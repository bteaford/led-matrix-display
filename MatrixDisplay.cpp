#include "led-matrix.h"
#include "MatrixOperations.h"
#include "ChristmasCountdownDisplay.h"
// #include "ScrollingImageDisplay.h"
#include "NCAAFScoreDisplay.h"

#include <csignal>
#include <Magick++.h>
#include <memory>


volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

using ImageVector = std::vector<Magick::Image>;

int main(const int argc, char *argv[]) {
    Magick::InitializeMagick(*argv);
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    const rgb_matrix::RGBMatrix::Options matrix_options;
    const rgb_matrix::RuntimeOptions runtime_opt;

    rgb_matrix::RGBMatrix *matrix = MatrixOperations::GenerateMatrix(matrix_options, runtime_opt, argc, argv);
    if (matrix == nullptr)
        return 1;
    rgb_matrix::FrameCanvas *offscreen_canvas = matrix->CreateFrameCanvas();

    std::vector<std::unique_ptr<Display>> displays;
    displays.push_back(std::make_unique<ChristmasCountdownDisplay>());
    // displays.push_back(std::make_unique<ScrollingImageDisplay>());
    // displays.push_back(std::make_unique<NCAAFScoreDisplay>());

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
