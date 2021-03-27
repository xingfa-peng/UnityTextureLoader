#pragma once
#include "RefCounter.h"

namespace Inking
{
    class ITextureLoader;

    class Texture : public RefCounter
    {
    protected:
        void* _native = nullptr;
        ITextureLoader* _textureLoader = nullptr;
    public:
        Texture(ITextureLoader* textureLoader);

        virtual ~Texture();

        void* GetNative()
        {
            return _native;
        }

        void SetNative(void* value)
        {
            _native = value;
        }
    };
}
