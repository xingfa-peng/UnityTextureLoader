#pragma once

#ifdef _OPENGLES_

#include "TextureLoaderOpenGLES.h"

namespace Inking
{
    class TextureLoaderOpenGLES2 : public TextureLoaderOpenGLES
    {
    public:
        TextureLoaderOpenGLES2()
            :TextureLoaderOpenGLES(2)
        {

        }
    };
}

#endif

