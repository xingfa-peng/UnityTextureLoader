:: cmake ...

cmake.exe ^
-H"." ^
-B"./build_android" ^
-DANDROID_ABI=armeabi-v7a ^
-DANDROID_PLATFORM=android-16 ^
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY="../Android/libs/armeabi-v7a" ^
-DCMAKE_BUILD_TYPE=Release ^
-DANDROID_NDK=%ANDROID_HOME%\ndk-bundle ^
-DCMAKE_CXX_FLAGS= ^
-DCMAKE_SYSTEM_NAME=Android ^
-DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a ^
-DCMAKE_SYSTEM_VERSION=16 ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
-DCMAKE_ANDROID_NDK=%ANDROID_HOME% ^
-DCMAKE_TOOLCHAIN_FILE=%ANDROID_HOME%\ndk-bundle\build\cmake\android.toolchain.cmake -G Ninja


:: make ...
ninja all -C build_android

:: cmake ...
cmake.exe ^
-H"." ^
-B"./build_android" ^
-DANDROID_ABI=arm64-v8a ^
-DANDROID_PLATFORM=android-16 ^
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY="../Android/libs/arm64-v8" ^
-DCMAKE_BUILD_TYPE=Release ^
-DANDROID_NDK=%ANDROID_HOME%\ndk-bundle ^
-DCMAKE_CXX_FLAGS= ^
-DCMAKE_SYSTEM_NAME=Android ^
-DCMAKE_ANDROID_ARCH_ABI=arm64-v8a ^
-DCMAKE_SYSTEM_VERSION=16 ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
-DCMAKE_ANDROID_NDK=%ANDROID_HOME% ^
-DCMAKE_TOOLCHAIN_FILE=%ANDROID_HOME%\ndk-bundle\build\cmake\android.toolchain.cmake -G Ninja


:: make ...
ninja all -C build_android

:: xcopy /Y /E "build_android/Android" "UnityResourceLoader\Assets\Inking\ResourceLoader\Plugins\Android"

pause