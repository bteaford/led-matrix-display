//
// Created by Brad on 12/20/25.
//

#include "Image.h"

Image::Image(const int x, const int y, const std::string &fileNameParam)
: Drawable(x, y) {
    std::vector<Magick::Image> loaded_images;
    try {
        Magick::readImages(&loaded_images, fileNameParam);
    } catch (std::exception &e) {
        if (e.what())
            fprintf(stderr, "%s\n", e.what());
    }
}

int Image::height() {
    return static_cast<int>(image.columns());
}

int Image::width() {
    return static_cast<int>(image.rows());
}

void Image::scale(const int width, const int height) {
    image.scale(Magick::Geometry(width, height));
}

void Image::draw(rgb_matrix::Canvas* canvas) {
    for (size_t y = 0; y < image.rows(); ++y) {
        for (size_t x = 0; x < image.columns(); ++x) {
            const Magick::Color &c = image.pixelColor(x, y);
            if (c.alphaQuantum() < 256) {
                canvas->SetPixel(x, y,
                                 MagickCore::ScaleQuantumToChar(c.redQuantum()),
                                 MagickCore::ScaleQuantumToChar(c.greenQuantum()),
                                 MagickCore::ScaleQuantumToChar(c.blueQuantum()));
            }
        }
    }
}