#pragma once

#include <thread>
using namespace std;
#include "RefCounter.h"
#include "IUnityGraphics.h"
#include "ColorSpace.h"

struct IUnityInterfaces;

namespace Inking
{
	class TextureLoadAsyncOperation;

	class ITextureLoader : public RefCounter
	{
	public:
		virtual TextureLoadAsyncOperation* LoadAsync(const Char* fileName, ColorSpace colorSpace = ColorSpace::Linear) = 0;

		virtual void Update() = 0;

		virtual void Unload(void* nativeTex) = 0;

		virtual void OnUnityPluginLoad(IUnityInterfaces* unityInterfaces) = 0;

		virtual void OnUnityRenderingEvent(int eventID) = 0;

		virtual void OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType) = 0;

		virtual void OnUnityPluginUnload() = 0;

		virtual TextureLoadAsyncOperation* LoadAsyncFromMemory(const void* buffer, int bufferLen, ColorSpace colorSpace) = 0;
	};
}
