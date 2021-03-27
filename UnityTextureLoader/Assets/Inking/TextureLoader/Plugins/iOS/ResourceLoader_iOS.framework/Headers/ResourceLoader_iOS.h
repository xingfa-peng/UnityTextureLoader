//
//  ResourceLoader_iOS.h
//  ResourceLoader_iOS
//
//  Created by  pc on 2021/3/19.
//

#import <Foundation/Foundation.h>

//! Project version number for ResourceLoader_iOS.
FOUNDATION_EXPORT double ResourceLoader_iOSVersionNumber;

//! Project version string for ResourceLoader_iOS.
FOUNDATION_EXPORT const unsigned char ResourceLoader_iOSVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ResourceLoader_iOS/PublicHeader.h>

class DpvrTexture2D;
class ResourceLoader;
class UnityResourceLoader;
class ResourceLoadAsyncOperation;
class Resource;

#define EXPORT

extern "C"
{
    EXPORT void* NativeTexture2D_GetNative(DpvrTexture2D* _this);

    EXPORT int NativeTexture2D_GetWidth(DpvrTexture2D* _this);

    EXPORT int NativeTexture2D_GetHeight(DpvrTexture2D* _this);

    EXPORT void NativeTexture2D_Release(DpvrTexture2D* _this);

    EXPORT ResourceLoadAsyncOperation* ResourceLoadAsyncOperation_New();
    
    EXPORT void ResourceLoadAsyncOperation_Release(ResourceLoadAsyncOperation* _this);

    EXPORT int ResourceLoadAsyncOperation_GetState(ResourceLoadAsyncOperation* _this);
    
    EXPORT const DpvrTexture2D* ResourceLoadAsyncOperation_GetResource(ResourceLoadAsyncOperation* _this);
    
    EXPORT UnityResourceLoader* ResourceLoader_GetInstance();
    
    EXPORT void ResourceLoader_Release(UnityResourceLoader* _this);

    EXPORT ResourceLoadAsyncOperation* ResourceLoader_LoadAsync(UnityResourceLoader* _this, const char* fileName);

    EXPORT void ResourceLoader_Update(UnityResourceLoader* _this);
    
    EXPORT void ResourceLoader_Unload(UnityResourceLoader* _this, void* native);
}
