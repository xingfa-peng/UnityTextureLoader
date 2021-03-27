#pragma once

#ifdef _OPENGLES_

#include "ITextureLoader.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <vector>
using namespace std;

namespace Inking
{

    class TextureLoadAsyncOperation;

    class TextureLoaderOpenGLES : public ITextureLoader
    {
    protected:
        EGLContext _shareContext;
        EGLContext _context;
        EGLDisplay _display = nullptr;
        EGLConfig _config = nullptr;
        EGLint _configID = 0;
        EGLSurface _surface = nullptr;

        thread _thread;
        mutex _mutexStage1;
        mutex _mutexStage2;

        static void LoadAsyncThreadFunc(TextureLoaderOpenGLES* _this);

        void _LoadAsyncThreadFunc();

        void Load(TextureLoadAsyncOperation* operation);

        list< TextureLoadAsyncOperation*> _stage1Operations;
        list< TextureLoadAsyncOperation*> _stage2Operations;

        int _version;
        bool isLoadThreadRuning = true;
    public:
        TextureLoaderOpenGLES(int version);

        virtual ~TextureLoaderOpenGLES();

        virtual TextureLoadAsyncOperation* LoadAsync(const Char * fileName);

        virtual void Update();

        EGLContext GetShareContext()
        {
            return _shareContext;
        }

        EGLContext GetContext()
        {
            return _context;
        }

        virtual void Unload(void* native);

        void Unload(GLuint native);

        void DoUnload();

        mutex _mutexUnloadTex;
        vector<GLuint> _unloadTexIDs;

        virtual void OnUnityPluginLoad(IUnityInterfaces* unityInterfaces);

        virtual void OnUnityRenderingEvent(int eventID);

        virtual void OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType) {};

        virtual void OnUnityPluginUnload() {}
    };
}


#endif