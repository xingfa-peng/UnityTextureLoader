#include "UnityTextureLoaderExports.h"
#include "UnityTextureLoader.h"
#include "Texture2D.h"
#include "TextureLoaderOpenGLES.h"
#include "TextureLoadAsyncOperation.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#include <stb_image.h>

extern "C"
{
    int Inking_Texture2D_GetWidth(Inking::Texture2D* _this)
    {
        return _this->GetWidth();
    }

    int Inking_Texture2D_GetHeight(Inking::Texture2D* _this)
    {
        return _this->GetHeight();
    }

    void Inking_Texture2D_Release(Inking::Texture2D* _this)
    {
        if (_this != nullptr)
        {
            _this->Release();
        }
    }

    void* Inking_Texture2D_GetNative(Inking::Texture2D* _this)
    {
        return _this->GetNative();
    }

    Inking::TextureLoadAsyncOperation* Inking_TextureLoadAsyncOperation_New() {
        return new Inking::TextureLoadAsyncOperation();
    }

    void Inking_TextureLoadAsyncOperation_Release(Inking::TextureLoadAsyncOperation* _this) {
        _this->Release();
    }

    int Inking_TextureLoadAsyncOperation_GetState(Inking::TextureLoadAsyncOperation* _this)
    {
        if (_this == nullptr)
            return 0;

        return (int)_this->GetState();
    }

    const Inking::Texture* Inking_TextureLoadAsyncOperation_GetTexture(Inking::TextureLoadAsyncOperation* _this)
    {
        return _this->GetTexture();
    }

    Inking::UnityTextureLoader* Inking_TextureLoader_GetInstance()
    {
        return Inking::UnityTextureLoader::GetInstance();
    }

    Inking::TextureLoadAsyncOperation* Inking_TextureLoader_LoadAsync(Inking::UnityTextureLoader* _this, const Char* fileName)
    {
        return _this->LoadAsync(fileName);
    }

    void Inking_TextureLoader_Update(Inking::UnityTextureLoader* _this)
    {
        _this->Update();
    }

    void Inking_TextureLoader_Unload(Inking::UnityTextureLoader* _this, void* native)
    {
        _this->Unload(native);
    }
}




