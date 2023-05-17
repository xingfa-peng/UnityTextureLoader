#pragma once
#include "Typedef.h"
#include "ColorSpace.h"


#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

namespace Inking
{
class UnityTextureLoader;
class TextureLoadAsyncOperation;
class Texture;
class Texture2D;
}

extern "C" 
{
    EXPORT void* Inking_Texture2D_GetNative(Inking::Texture2D* _this);

    EXPORT int Inking_Texture2D_GetWidth(Inking::Texture2D* _this);

    EXPORT int Inking_Texture2D_GetHeight(Inking::Texture2D* _this);

    EXPORT void Inking_Texture2D_Release(Inking::Texture2D* _this);

    EXPORT Inking::TextureLoadAsyncOperation* Inking_TextureLoadAsyncOperation_New();
    
    EXPORT void Inking_TextureLoadAsyncOperation_Release(Inking::TextureLoadAsyncOperation* _this);

    EXPORT int Inking_TextureLoadAsyncOperation_GetState(Inking::TextureLoadAsyncOperation* _this);
    
    EXPORT const Inking::Texture* Inking_TextureLoadAsyncOperation_GetTexture(Inking::TextureLoadAsyncOperation* _this);
    
    EXPORT Inking::UnityTextureLoader* Inking_TextureLoader_GetInstance();
    
	EXPORT Inking::TextureLoadAsyncOperation* Inking_TextureLoader_LoadAsync(Inking::UnityTextureLoader* _this, const Char* fileName, Inking::ColorSpace colorSpace);

    EXPORT void Inking_TextureLoader_Update(Inking::UnityTextureLoader* _this);
    
    EXPORT void Inking_TextureLoader_Unload(Inking::UnityTextureLoader* _this, void* native);
 
    EXPORT Inking::TextureLoadAsyncOperation* Inking_TextureLoader_LoadAsyncFromMemory(Inking::UnityTextureLoader* _this, const void* buffer, int bufferLen, Inking::ColorSpace colorSpace);
}
