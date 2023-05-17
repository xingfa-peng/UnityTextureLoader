:: cmake ...

cmake.exe ^
-H"." ^
-B"./_build_android/armeabi-v7a" ^
-DANDROID_ABI=armeabi-v7a ^
-DANDROID_PLATFORM=android-16 ^
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY="../../../lib/Android/libs/armeabi-v7a" ^
-DCMAKE_BUILD_TYPE=Release ^
-DANDROID_NDK=D:\Documents\Android\NDK\android-ndk-r16b\ ^
-DCMAKE_CXX_FLAGS= ^
-DCMAKE_SYSTEM_NAME=Android ^
-DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a ^
-DCMAKE_SYSTEM_VERSION=16 ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
-DCMAKE_ANDROID_NDK=D:\Documents\Android\NDK\android-ndk-r16b\ ^
-DANDROID_STL=c++_static ^
-DCMAKE_TOOLCHAIN_FILE=D:\Documents\Android\NDK\android-ndk-r16b\build\cmake\android.toolchain.cmake -G Ninja


:: make ...
ninja all -C _build_android/armeabi-v7a

:: cmake ...
cmake.exe ^
-H"." ^
-B"./_build_android/arm64-v8a" ^
-DANDROID_ABI=arm64-v8a ^
-DANDROID_PLATFORM=android-16 ^
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY="../../../lib/Android/libs/arm64-v8a" ^
-DCMAKE_BUILD_TYPE=Release ^
-DANDROID_NDK=D:\Documents\Android\NDK\android-ndk-r16b ^
-DCMAKE_CXX_FLAGS= ^
-DCMAKE_SYSTEM_NAME=Android ^
-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a ^
-DCMAKE_SYSTEM_VERSION=16 ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
-DCMAKE_ANDROID_NDK=D:\Documents\Android\NDK\android-ndk-r16b ^
-DANDROID_STL=c++_static ^
-DCMAKE_TOOLCHAIN_FILE=D:\Documents\Android\NDK\android-ndk-r16b\build\cmake\android.toolchain.cmake -G Ninja


:: make ...
ninja all -C _build_android/arm64-v8a


:: xcopy /Y /E "build_android/Android" "UnityResourceLoader\Assets\Inking\ResourceLoader\Plugins\Android"

pause