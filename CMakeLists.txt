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

# ---- MatrixOperations library ----
add_library(MatrixOperations STATIC
        src/util/MatrixOperations.cpp
)

target_include_directories(MatrixOperations PUBLIC
        ${CMAKE_SOURCE_DIR}/src/include
)

target_include_directories(MatrixOperations SYSTEM PUBLIC
        ${ImageMagick_INCLUDE_DIRS}
)

target_link_libraries(MatrixOperations PUBLIC
        rgbmatrix
        ${ImageMagick_LIBRARIES}
)

target_compile_options(MatrixOperations PRIVATE
        -Wall
        -Wextra
        -Wno-unused-parameter
)

target_compile_definitions(MatrixOperations PUBLIC
        MAGICKCORE_QUANTUM_DEPTH=16
        MAGICKCORE_HDRI_ENABLE=0
)


add_library(Display STATIC
        src/displays/Display.cpp
        src/displays/ChristmasCountdownDisplay.cpp
        src/displays/ScrollingImageDisplay.cpp
)

target_include_directories(Display PUBLIC
        ${CMAKE_SOURCE_DIR}/src/include
        ${CMAKE_SOURCE_DIR}/src/displays
)

target_link_libraries(Display PUBLIC
        MatrixOperations
)

# ---- Executables (at project root) ----

add_executable(MatrixDisplay
        MatrixDisplay.cpp
)

target_link_libraries(MatrixDisplay PRIVATE
        MatrixOperations
        Display
)
