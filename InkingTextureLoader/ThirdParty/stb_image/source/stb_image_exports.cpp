#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#if TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#endif

#if __cplusplus
extern "C" {
#endif
#if TARGET_OS_IPHONE
    STBIDEF unsigned char *_stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp)
    {
        return stbi_load_from_memory(buffer, len, x, y, comp, req_comp);
    }

    STBIDEF void _stbi_image_free(void* ptr)
    {
        stbi_image_free(ptr);
    }
#endif 

#if defined(_WIN32) || defined(_WIN64)

    _declspec(dllexport) unsigned char *_stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp)
    {
        return stbi_load_from_memory(buffer, len, x, y, comp, req_comp);
    }

    _declspec(dllexport) void _stbi_image_free(void* ptr)
    {
        stbi_image_free(ptr);
    }

    _declspec(dllexport) void _stbi_resize(const unsigned char* input, int input_width, int input_height, unsigned char* output, int output_width, int output_height, int comp)
    {
        stbir_resize_uint8(input, input_width, input_height, 0, 
            output, output_width, output_height, 0, comp);
    }
#endif

#if ANDROID
    unsigned char *_stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp)
    {
        return stbi_load_from_memory(buffer, len, x, y, comp, req_comp);
    }

    void _stbi_image_free(void* ptr)
    {
        stbi_image_free(ptr);
    }

    void _stbi_resize(const unsigned char* input, int input_width, int input_height, unsigned char* output, int output_width, int output_height, int comp)
    {
        stbir_resize_uint8(input, input_width, input_height, 0,
            output, output_width, output_height, 0, comp);
    }
#endif
#if __cplusplus
}
#endif
