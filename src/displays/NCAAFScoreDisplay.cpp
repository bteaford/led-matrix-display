//
// Created by Brad on 12/19/25.
//

#include "NCAAFScoreDisplay.h"

#include <unistd.h>

void NCAAFScoreDisplay::show_indefinitely(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {
    Magick::Image image1 = MatrixOperations::loadAndScaleImage("/home/rpi/projects/led-matrix-display/img/logos/ncaa/Georgia_Bulldogs_logo-300x300.png", matrix.height(), matrix.height());
    Magick::Image image2 = MatrixOperations::loadAndScaleImage("/home/rpi/projects/led-matrix-display/img/logos/ncaa/Florida_Gators_logo-300x300.png", matrix.height(), matrix.height());
    int x = matrix.width() - image2.columns();
    int y = matrix.height() - image2.rows();
    MatrixOperations::ImageSpec is1 = {image1, 0, 0};
    MatrixOperations::ImageSpec is2 = {image2, x, 0};
    MatrixOperations::DisplayImage(is1, canvas);
    MatrixOperations::DisplayImage(is2, canvas);

    // font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");

    // rgb_matrix::DrawText(canvas, font, image2.columns() + 1, 14, rgb_matrix::Color(255, 255, 255), nullptr, "24");
    // rgb_matrix::DrawText(canvas, font, image2.columns() + 1, matrix.height(), rgb_matrix::Color(255, 255, 255), nullptr, "34");
    matrix.SwapOnVSync(canvas);
    while (!interrupt_received) {
        usleep(100000);
    }
}

void NCAAFScoreDisplay::show(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {

}
