cmake_minimum_required(VERSION 3.16)

project(ChristmasCountdown LANGUAGES CXX)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Warnings & optimization ----
add_compile_options(
    -Wall
    -Wextra
    -Wno-unused-parameter
)

# ---- rpi-rgb-led-matrix paths ----
set(RGB_ROOT ${CMAKE_SOURCE_DIR}/lib/rpi-rgb-led-matrix)
set(RGB_INCLUDE_DIR ${RGB_ROOT}/include)
set(RGB_LIBRARY ${RGB_ROOT}/lib/librgbmatrix.a)

# ---- Declare imported library ----
add_library(rgbmatrix STATIC IMPORTED)

set_target_properties(rgbmatrix PROPERTIES
    IMPORTED_LOCATION ${RGB_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${RGB_INCLUDE_DIR}
)

# ---- Main executable ----
add_executable(ChristmasCountdown
    ChristmasCountdown.cc
)

# ---- Link everything ----
target_link_libraries(ChristmasCountdown PRIVATE
    rgbmatrix
    rt
    m
    pthread
)
