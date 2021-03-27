#ifdef _D3D11_

#include "TextureLoaderD3D11.h"
#include <D3DX11tex.h>
#include "Texture2D.h"

#define STBI_WINDOWS_UTF8
#include "stb_image.h"
#include "IUnityGraphicsD3D11.h"

namespace Inking
{

    TextureLoaderD3D11::TextureLoaderD3D11()
    {

    }

    TextureLoaderD3D11::~TextureLoaderD3D11()
    {
        isLoadThreadRuning = false;
        _thread.join();
    }

    void TextureLoaderD3D11::AsyncLoadThreadFunc(TextureLoaderD3D11* _this)
    {
        _this->_AsyncLoadThreadFunc();
    }

    void TextureLoaderD3D11::LoadShared(TextureLoadAsyncOperation* operation)
    {
        operation->SetState(TextureLoadAsyncOperationState::Loading);

        const Char* fileName = operation->GetFileName();

        ID3D11Texture2D* d3d11Texture2D = nullptr;

        int width = 0;
        int height = 0;
        int comp = 0;

        stbi_set_flip_vertically_on_load(1);

        char fileName2[1024] = "";
        stbi_convert_wchar_to_utf8(fileName2, 1024, fileName);

        auto pixels = stbi_load(fileName2, &width, &height, &comp, 4);
        if (pixels == nullptr) {
            operation->OnLoadFailed();
            return;
        }

        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = pixels;
        data.SysMemPitch = width * 4;
        data.SysMemSlicePitch = 1;

        HRESULT hr = _device->CreateTexture2D(&desc, &data, &d3d11Texture2D);

        stbi_image_free(pixels);

        if (FAILED(hr))
        {
            operation->OnLoadFailed();
            return;
        }

        IDXGIResource* pResource = nullptr;
        hr = d3d11Texture2D->QueryInterface(__uuidof(IDXGIResource), reinterpret_cast<void**>(&pResource));
        if (FAILED(hr)) {
            operation->OnLoadFailed();
            return;
        }

        HANDLE textureSharedHandle = INVALID_HANDLE_VALUE;
        if (SUCCEEDED(hr))
        {
            pResource->GetSharedHandle(&textureSharedHandle);

            Texture2D* texture2D = new Texture2D(this);
            texture2D->SetNative(textureSharedHandle);
            texture2D->SetWidth(width);
            texture2D->SetHeight(height);

            operation->SetTexture(texture2D);
        }

        d3d11Texture2D->Release();
    }

    void TextureLoaderD3D11::Load(TextureLoadAsyncOperation* operation)
    {
        LoadShared(operation);

        _stage2Mutex.lock();
        _stage2Operations.push_front(operation);
        _stage2Mutex.unlock();
    }

    void TextureLoaderD3D11::_AsyncLoadThreadFunc()
    {
        while (isLoadThreadRuning)
        {
            Sleep(0);

            _stage1Mutex.lock();

            auto size = this->_stage1Operations.size();

            if (size == 0)
            {
                _stage1Mutex.unlock();
                continue;
            }

            auto operation = this->_stage1Operations.front();
            this->_stage1Operations.pop_front();
            _stage1Mutex.unlock();

            Load(operation);

        }
    }

    TextureLoadAsyncOperation* TextureLoaderD3D11::LoadAsync(const Char* fileName)
    {
        _stage1Mutex.lock();
        auto operation = new TextureLoadAsyncOperation();
        _stage1Operations.push_back(operation);
        operation->SetFileName(fileName);
        _stage1Mutex.unlock();

        return operation;
    }

    void TextureLoaderD3D11::Update()
    {
        _stage2Mutex.lock();
        
        if (_stage2Operations.size() != 0)
        {
            for (auto operation : _stage2Operations)
            {
                if (operation->GetState() == TextureLoadAsyncOperationState::LoadFailed)
                {
                    operation->SetTexture(nullptr);
                    continue;
                }

                Texture2D* texture2D = (Texture2D*)operation->GetTexture();

                HANDLE handle = (HANDLE)texture2D->GetNative();
                if (handle != INVALID_HANDLE_VALUE)
                {
                    ID3D11Texture2D* d3d11Texture2D = nullptr;
                    ID3D11ShaderResourceView* srv = nullptr;
                    
                    HRESULT hr = _device->OpenSharedResource(handle, __uuidof(ID3D11Texture2D), (void**)&d3d11Texture2D);
                    if (SUCCEEDED(hr))
                    {
                        hr = _device->CreateShaderResourceView(d3d11Texture2D, NULL, &srv);
                        if (SUCCEEDED(hr))
                        {
                            texture2D->SetNative(srv);
                            operation->SetState(TextureLoadAsyncOperationState::LoadSucceed);
                            d3d11Texture2D->Release();
                            continue;
                        }
                    }

                    operation->SetTexture(nullptr);
                    operation->SetState(TextureLoadAsyncOperationState::LoadFailed);
                }
            }

            _stage2Operations.clear();
        }

        _stage2Mutex.unlock();
    }

    void TextureLoaderD3D11::Unload(void* nativeTex)
    {
        ID3D11ShaderResourceView * srv = (ID3D11ShaderResourceView *)nativeTex;
        if(srv)
            srv->Release();
    }

    void TextureLoaderD3D11::OnUnityPluginLoad(IUnityInterfaces* unityInterfaces)
    {
        IUnityGraphics* graphics = unityInterfaces->Get<IUnityGraphics>();
        auto renderer = graphics->GetRenderer();
        switch (renderer)
        {
        case kUnityGfxRendererD3D11:
        {
            auto graphicsD3D11 = unityInterfaces->Get<IUnityGraphicsD3D11>();
            _device = graphicsD3D11->GetDevice();
            _thread = thread(AsyncLoadThreadFunc, this);
            break;
        }
        default:
            break;
        }
    }

    void TextureLoaderD3D11::OnUnityRenderingEvent(int eventID)
    {

    }
}


#endif