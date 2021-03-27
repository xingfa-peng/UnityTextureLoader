#pragma once
#include "Typedef.h"
#include "Texture.h"

namespace Inking
{
    class Texture2D : public Texture
    {
    protected:
        int _width = 0;
        int _height = 0;
    public:
        Texture2D(ITextureLoader* textureLoader)
            :Texture(textureLoader)
        {

        }

        virtual ~Texture2D()
        {

        }

        int GetWidth()
        {
            return _width;
        }

        int GetHeight()
        {
            return _height;
        }

        void SetWidth(int value) {
            _width = value;
        }

        void SetHeight(int value) {
            _height = value;
        }
    };
}
