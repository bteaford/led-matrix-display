// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
//
// Example how to display an image, including animated images using
// ImageMagick. For a full utility that does a few more things, have a look
// at the led-image-viewer in ../utils
//
// Showing an image is not so complicated, essentially just copy all the
// pixels to the canvas. How to get the pixels ? In this example we're using
// the graphicsmagick library as universal image loader library that
// can also deal with animated images.
// You can of course do your own image loading or use some other library.
//
// This requires an external dependency, so install these first before you
// can call `make image-example`
//   sudo apt-get update
//   sudo apt-get install libgraphicsmagick++-dev libwebp-dev -y
//   make image-example

#include "led-matrix.h"
#include "MatrixOperations.h"
#include "ChristmasCountdownDisplay.h"
// #include "ScrollingImageDisplay.h"

#include <csignal>
#include <Magick++.h>
#include <memory>


// Make sure we can exit gracefully when Ctrl-C is pressed.
volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

using ImageVector = std::vector<Magick::Image>;

int main(int argc, char *argv[]) {
    Magick::InitializeMagick(*argv);
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    // Initialize the RGB matrix with
    const rgb_matrix::RGBMatrix::Options matrix_options;
    const rgb_matrix::RuntimeOptions runtime_opt;

    rgb_matrix::RGBMatrix *matrix = MatrixOperations::GenerateMatrix(matrix_options, runtime_opt, argc, argv);
    if (matrix == nullptr)
        return 1;
    rgb_matrix::FrameCanvas *offscreen_canvas = matrix->CreateFrameCanvas();

    std::vector<std::unique_ptr<Display>> displays;
    displays.push_back(std::make_unique<ChristmasCountdownDisplay>());
    // displays.push_back(std::make_unique<ScrollingImageDisplay>());

    for (const auto& display : displays) {
        display->load();
    }

    while (!interrupt_received) {
        if (displays.size() == 1) {
            displays[0]->show_indefinitely(*matrix, offscreen_canvas, interrupt_received);
        } else {
            for (const auto& display : displays) {
                display->show(*matrix, offscreen_canvas, interrupt_received);
            }
        }
    }

    matrix->Clear();
    delete matrix;

    return 0;
}
