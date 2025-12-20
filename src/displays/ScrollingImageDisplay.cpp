#include <unistd.h>
#include <Magick++.h>

#include "ScrollingImageDisplay.h"

void ScrollingImageDisplay::show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) {

    const std::string filename = "/home/rpi/projects/led-matrix-display/img/199-1995553_ohio-state-university-block-o.png";
    const Magick::Image image = MatrixOperations::loadAndScaleImage(filename, matrix.width(), static_cast<int>(matrix.height() / 1.3));

    font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");

    MatrixOperations::ImageSpec image_spec = {
        image, canvas->width(), canvas->height() / 2 - 7
    };
    const int columns = static_cast<int>(image.columns());
    while (image_spec.x >= columns * -1 && !interrupt_received) {
        canvas->Clear();
        MatrixOperations::DisplayImage(image_spec, canvas);
        rgb_matrix::DrawText(canvas, font, image_spec.x, canvas->height() / 4, rgb_matrix::Color(255, 255, 255), nullptr, "OSU");
        canvas = matrix.SwapOnVSync(canvas);
        image_spec.x--;
        usleep(100000 / 2);
    }
}

void ScrollingImageDisplay::show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) {

    const std::string filename = "/home/rpi/projects/led-matrix-display/img/199-1995553_ohio-state-university-block-o.png";
    const Magick::Image image = MatrixOperations::loadAndScaleImage(filename, matrix.width(), static_cast<int>(matrix.height() / 1.3));

    font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");

    MatrixOperations::ImageSpec image_spec = {
        image, canvas->width(), canvas->height() / 2 - 7
    };
    while (!interrupt_received) {
        canvas->Clear();
        MatrixOperations::DisplayImage(image_spec, canvas);
        rgb_matrix::DrawText(canvas, font, image_spec.x, canvas->height() / 4, rgb_matrix::Color(255, 255, 255), nullptr, "OSU");
        canvas = matrix.SwapOnVSync(canvas);
        image_spec.x--;
        if (image_spec.x + image_spec.image.columns() < 0) image_spec.x = matrix.width();
        usleep(100000 / 2);
    }
}
