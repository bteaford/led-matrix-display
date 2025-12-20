#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <Magick++.h>

#include "led-matrix.h"

namespace MatrixOperations {

    struct ImageSpec {
        Magick::Image image;
        int x, y;
    };

    rgb_matrix::RGBMatrix* GenerateMatrix(rgb_matrix::RGBMatrix::Options matrix_options, rgb_matrix::RuntimeOptions runtime_opt, int argc, char *argv[]);
    Magick::Image loadAndScaleImage(const std::string& fileName, int width, int height);
    void DisplayImage(const ImageSpec &image_spec, rgb_matrix::Canvas *canvas);
}

#endif //MATRIXOPERATIONS_H