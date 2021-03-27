#include "Texture.h"
#include "ITextureLoader.h"

namespace Inking
{
    Texture::Texture(ITextureLoader* textureLoader) 
        :_textureLoader(textureLoader)
    {

    }

    Texture::~Texture()
    {
        if (_textureLoader != nullptr)
        {
            _textureLoader->Unload(_native);
        }
    }

}

