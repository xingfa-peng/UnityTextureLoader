#pragma once


#ifdef _WIN32
#include <d3d11.h>
#include "IUnityGraphicsD3D11.h"
#endif
#include "IUnityInterface.h"
#include "IUnityGraphics.h"


#include "ITextureLoader.h"

namespace Inking
{
    class UnityTextureLoader : public ITextureLoader
    {
        ITextureLoader* _impl = nullptr;

        UnityTextureLoader();
    public:
        static IUnityInterfaces* g_unityInterfaces;

        virtual TextureLoadAsyncOperation* LoadAsync(const Char * fileName, ColorSpace colorSpace)
        {
            if (_impl == nullptr)
                return nullptr;

            return _impl->LoadAsync(fileName, colorSpace);
        }

        virtual void Update()
        {
            if (_impl != nullptr)
            {
                _impl->Update();
            }
        }

        static UnityTextureLoader* GetInstance()
        {
            static UnityTextureLoader inst;
            return &inst;
        }

        virtual void Unload(void* native)
        {
            if (_impl != nullptr)
            {
                _impl->Unload(native);
            }
        }

        virtual void OnUnityPluginLoad(IUnityInterfaces* unityInterfaces);

        virtual void OnUnityRenderingEvent(int eventID);

        virtual void OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);;

        virtual void OnUnityPluginUnload() {}


		virtual TextureLoadAsyncOperation* LoadAsyncFromMemory(const void* buffer, int bufferLen, ColorSpace colorSpace);
    };

}
