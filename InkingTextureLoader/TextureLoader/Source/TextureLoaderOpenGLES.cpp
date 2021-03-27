#ifdef _OPENGLES_

#include "TextureLoaderOpenGLES.h"
#include "Texture2D.h"

#include "stb_image.h"

#include <unistd.h>

#include "TextureLoadAsyncOperation.h"
#include "TextureLoadAsyncOpeartionState.h"

namespace Inking
{
    void TextureLoaderOpenGLES::LoadAsyncThreadFunc(TextureLoaderOpenGLES* _this)
    {
        _this->_LoadAsyncThreadFunc();
    }

    TextureLoaderOpenGLES::TextureLoaderOpenGLES(int version)
        :_version(version)
    {

    }

    TextureLoaderOpenGLES::~TextureLoaderOpenGLES()
    {
        isLoadThreadRuning = false;
        this->_thread.join();
    }

    void TextureLoaderOpenGLES::_LoadAsyncThreadFunc()
    {
        EGLConfig configs[512] = {};
        EGLint numConfigs = 0;
        eglGetConfigs(_display, configs, 512, &numConfigs);
        EGLConfig contextConfig = 0;
        for (int i = 0; i < numConfigs; i++)
        {
            EGLint tmpConfigId;
            eglGetConfigAttrib(_display, configs[i], EGL_CONFIG_ID, &tmpConfigId);
            if (tmpConfigId == _configID)
            {
                contextConfig = configs[i];
                break;
            }
        }

        //Check if the incoming configuration supports GLES3
        EGLint renderableType = 0;
        eglGetConfigAttrib(_display, contextConfig, EGL_RENDERABLE_TYPE, &renderableType);

        //Log the surface channel bit depths (prefer an 888 surface with no depth)
        EGLint r, g, b, d, s;
        eglGetConfigAttrib(_display, contextConfig, EGL_RED_SIZE, &r);
        eglGetConfigAttrib(_display, contextConfig, EGL_GREEN_SIZE, &g);
        eglGetConfigAttrib(_display, contextConfig, EGL_BLUE_SIZE, &b);
        eglGetConfigAttrib(_display, contextConfig, EGL_DEPTH_SIZE, &d);
        eglGetConfigAttrib(_display, contextConfig, EGL_SAMPLES, &s);

        EGLint contextAttribs[] =
        {
            EGL_CONTEXT_CLIENT_VERSION, TextureLoaderOpenGLES::_version,
            EGL_NONE
        };

        _context = eglCreateContext(_display, contextConfig, _shareContext, contextAttribs);

        eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, _context);

        while (true)
        {
            sleep(0);

            DoUnload();

            if (_context == nullptr)
            {
                continue;
            }

            _mutexStage1.lock();

            auto size = _stage1Operations.size();
            if (size == 0) {
                _mutexStage1.unlock();
                continue;
            }

            auto operation = _stage1Operations.front();
            _stage1Operations.pop_front();

            _mutexStage1.unlock();

            Load(operation);
        }
    }

    void TextureLoaderOpenGLES::Load(TextureLoadAsyncOperation* operation)
    {
        operation->SetState(TextureLoadAsyncOperationState::Loading);
        int width = 0;
        int height = 0;
        int comp = 0;
        auto fileName = operation->GetFileName();

        stbi_set_flip_vertically_on_load(1);
        auto pixels = stbi_load(fileName, &width, &height, &comp, 4);

        Texture2D* texture2D = new Texture2D(this);
        operation->SetTexture(texture2D);
        GLuint texID = 0;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(pixels);

        texture2D->SetNative((void*)(texID));
        texture2D->SetWidth(width);
        texture2D->SetHeight(height);
        operation->SetState(TextureLoadAsyncOperationState::LoadSucceed);


    }

    TextureLoadAsyncOperation* TextureLoaderOpenGLES::LoadAsync(const Char * fileName)
    {
        _mutexStage1.lock();
        TextureLoadAsyncOperation* operation = new TextureLoadAsyncOperation();
        _stage1Operations.push_back(operation);
        operation->SetFileName(fileName);
        _mutexStage1.unlock();
        return operation;
    }

    void TextureLoaderOpenGLES::Update()
    {

    }

    void TextureLoaderOpenGLES::Unload(void* native)
    {
        Unload((GLuint)(GLuint64)native);
    }

    void TextureLoaderOpenGLES::Unload(GLuint native)
    {
        _mutexUnloadTex.lock();
        _unloadTexIDs.push_back(native);
        _mutexUnloadTex.unlock();
    }

    void TextureLoaderOpenGLES::DoUnload()
    {
        _mutexUnloadTex.lock();
        auto size = _unloadTexIDs.size();

        if (size != 0)
        {
            glDeleteTextures(size, _unloadTexIDs.data());
            _unloadTexIDs.clear();
        }

        _mutexUnloadTex.unlock();
    }

    void TextureLoaderOpenGLES::OnUnityPluginLoad(IUnityInterfaces* unityInterfaces)
    {

    }

    void TextureLoaderOpenGLES::OnUnityRenderingEvent(int eventID)
    {
        switch (eventID)
        {
        case 1:
        {
            _display = eglGetCurrentDisplay();

            _surface = eglGetCurrentSurface(EGL_DRAW);

            eglQueryContext(_display, _shareContext, EGL_CONFIG_ID, &_configID);

            _shareContext = eglGetCurrentContext();

            _thread = thread(LoadAsyncThreadFunc, this);
            break;
        }
        default:
            break;
        }

    }
}

#endif
