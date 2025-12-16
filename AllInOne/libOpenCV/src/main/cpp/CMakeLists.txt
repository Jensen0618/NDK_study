
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).

# 声明项目名称，可以通过${PROJECT_NAME}访问。
# 由于这是顶层CMake文件，也可以通过${CMAKE_PROJECT_NAME}访问。
# 在顶层CMake中这两个值是相同的。
project("main")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.

# 创建共享库
add_library(
        # 库名称，由project()命令定义，java层需调用System.loadLibrary("${CMAKE_PROJECT_NAME}")
        ${CMAKE_PROJECT_NAME}
        # 声明为动态库
        SHARED
        # 源文件列表，路径相对于当前CMake文件
        main.cpp
        BitmapMatUtils.cpp
)


#opencv
#指定头文件搜索路径，以当前CMakeLists.txt文件的目录为起点
include_directories(${CMAKE_SOURCE_DIR}/)
add_library(
        opencv-lib # name
        SHARED
        # 将外部预构建的库文件导入项目
        IMPORTED)

# 导入外部预构建的库文件后需通过属性指定库文件路径
set_target_properties(
        opencv-lib # name
        PROPERTIES IMPORTED_LOCATION # 路径
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_java3.so)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
# 用于指定目标库（此处为 ${CMAKE_PROJECT_NAME}）在链接阶段需要依赖的库。
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        opencv-lib
        # List libraries link to the target library
        jnigraphics
        android
        log)
