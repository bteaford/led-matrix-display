cmake_minimum_required(VERSION 3.16)

project(MatrixDisplay LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies ----
find_package(ImageMagick COMPONENTS Magick++ MagickCore REQUIRED)
find_package(Threads REQUIRED)

# ---- rpi-rgb-led-matrix (prebuilt library) ----
set(RGB_ROOT ${CMAKE_SOURCE_DIR}/lib/rpi-rgb-led-matrix)

add_library(rgbmatrix INTERFACE)

target_include_directories(rgbmatrix INTERFACE
        ${RGB_ROOT}/include
)

target_link_libraries(rgbmatrix INTERFACE
        ${RGB_ROOT}/lib/librgbmatrix.a
)

# ---- Util library ----
add_library(Util STATIC
        src/util/MatrixOperations.cpp
        src/util/Drawable.cpp
        src/util/Text.cpp
        src/util/Image.cpp
        src/util/Screen.cpp
)

target_include_directories(Util PUBLIC
        ${CMAKE_SOURCE_DIR}/src/util
)

target_include_directories(Util SYSTEM PUBLIC
        ${ImageMagick_INCLUDE_DIRS}
)

target_link_libraries(Util PUBLIC
        rgbmatrix
        ${ImageMagick_LIBRARIES}
)

target_compile_options(Util PRIVATE
        -Wall
        -Wextra
        -Wno-unused-parameter
)

target_compile_definitions(Util PUBLIC
        MAGICKCORE_QUANTUM_DEPTH=16
        MAGICKCORE_HDRI_ENABLE=0
)


add_library(Displays STATIC
        src/displays/Display.cpp
        src/displays/ChristmasCountdownDisplay.cpp
        src/displays/ScrollingImageDisplay.cpp
        src/displays/NCAAFScoreDisplay.cpp
        src/displays/StaticImageDisplay.cpp
        src/displays/StaticImageDisplay.h
)

target_include_directories(Displays PUBLIC
        ${CMAKE_SOURCE_DIR}/src/util
        ${CMAKE_SOURCE_DIR}/src/displays
)

target_link_libraries(Displays PUBLIC
        Util
)

# ---- Executables (at project root) ----

add_executable(MatrixDisplay
        MatrixDisplay.cpp
)

target_link_libraries(MatrixDisplay PRIVATE
        Util
        Displays
)
