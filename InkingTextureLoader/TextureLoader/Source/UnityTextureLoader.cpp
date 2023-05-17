#include "UnityTextureLoader.h"
#include "TextureLoaderD3D11.h"
#include "TextureLoaderOpenGLES.h"
#include "TextureLoaderOpenGLES2.h"
#include "TextureLoaderOpenGLES3.h"

static void UNITY_INTERFACE_API
OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

// Unity 插件加载事件
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
	Inking::UnityTextureLoader::g_unityInterfaces = unityInterfaces;

	Inking::UnityTextureLoader::GetInstance()->OnUnityPluginLoad(unityInterfaces);

	auto graphics = unityInterfaces->Get<IUnityGraphics>();

	graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
	Inking::UnityTextureLoader::GetInstance()->OnUnityPluginUnload();
	//
	auto graphics = Inking::UnityTextureLoader::g_unityInterfaces->Get<IUnityGraphics>();
	graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
	Inking::UnityTextureLoader::g_unityInterfaces = nullptr;
}

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	Inking::UnityTextureLoader::GetInstance()->OnUnityRenderingEvent(eventID);
}

static void UNITY_INTERFACE_API
OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	Inking::UnityTextureLoader::GetInstance()->OnGraphicsDeviceEvent(eventType);
}

// Freely defined function to pass a callback to plugin-specific scripts   自由定义的函数，用来传递给插件相关代码的回调
extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}

namespace Inking
{

    IUnityInterfaces* UnityTextureLoader::g_unityInterfaces = nullptr;

	UnityTextureLoader::UnityTextureLoader()
	{

	}

	void UnityTextureLoader::OnUnityPluginLoad(IUnityInterfaces* unityInterfaces)
	{
		IUnityGraphics* graphics = unityInterfaces->Get<IUnityGraphics>();
		auto renderer = graphics->GetRenderer();
		switch (renderer)
		{
		case kUnityGfxRendererD3D11:
		{
#ifdef _D3D11_
            _impl = new TextureLoaderD3D11();
#endif
			break;
		}
		case kUnityGfxRendererNull:
			break;
		case kUnityGfxRendererOpenGLES20:
		{
#ifdef _OPENGLES_
            _impl = new TextureLoaderOpenGLES2();
#endif
			break;
		}
		case kUnityGfxRendererOpenGLES30:
		{
#ifdef _OPENGLES_
            _impl = new TextureLoaderOpenGLES3();
#endif
			break;
		}
		case kUnityGfxRendererPS4:
			break;
		case kUnityGfxRendererXboxOne:
			break;
		case kUnityGfxRendererMetal:
			break;
		case kUnityGfxRendererOpenGLCore:
			break;
		case kUnityGfxRendererD3D12:
			break;
		case kUnityGfxRendererVulkan:
			break;
		case kUnityGfxRendererNvn:
			break;
		case kUnityGfxRendererXboxOneD3D12:
			break;
		default:
			break;
		}

        if (_impl != nullptr)
            _impl->OnUnityPluginLoad(unityInterfaces);
	}

	void UnityTextureLoader::OnUnityRenderingEvent(int eventID)
	{
        if (_impl != nullptr)
            _impl->OnUnityRenderingEvent(eventID);
	}

	void UnityTextureLoader::OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
	{
		int i = 0;
		switch (eventType)
		{
		case kUnityGfxDeviceEventInitialize:
		{

			//TODO: user initialization code
			break;
		}
		case kUnityGfxDeviceEventShutdown:
		{
			//TODO: user shutdown code
			break;
		}
		case kUnityGfxDeviceEventBeforeReset:
		{
			//TODO: user Direct3D 9 code
			break;
		}
		case kUnityGfxDeviceEventAfterReset:
		{
			//TODO: user Direct3D 9 code
			break;
		}
		};

        if (_impl)
		{
            _impl->OnGraphicsDeviceEvent(eventType);
		}
	}

	TextureLoadAsyncOperation* UnityTextureLoader::LoadAsyncFromMemory(const void* buffer, int bufferLen, ColorSpace colorSpace)
	{
		if (!_impl)
			return nullptr;
		
		return _impl->LoadAsyncFromMemory(buffer, bufferLen, colorSpace);
	}

}