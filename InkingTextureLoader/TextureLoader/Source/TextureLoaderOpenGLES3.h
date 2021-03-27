#pragma once
#include "TextureLoaderOpenGLES.h"

#ifdef _OPENGLES_

namespace Inking
{

    class TextureLoaderOpenGLES3 : public TextureLoaderOpenGLES
    {
    public:

        TextureLoaderOpenGLES3()
            :TextureLoaderOpenGLES(3)
        {

        }

        virtual ~TextureLoaderOpenGLES3() {}

    };
}


#endif