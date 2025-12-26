#include "StaticImageDisplay.h"

#include <unistd.h>
#include <bits/getopt_core.h>

StaticImageDisplay::StaticImageDisplay(const int argc, char **argv) : screen(Screen(0, 0)) {
    this->argc = argc;
    this->argv = argv;
}

void StaticImageDisplay::load() {
    int opt, width = -1, height = -1;
    char* filename = nullptr;
    while ((opt = getopt(argc, argv, "i:w:h")) != -1) {
        switch (opt) {
            case 'i': {
                filename = optarg;
                break;
            }
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            default:
                break;
        }
    }

    if (filename != nullptr) {
        auto image = Image(0, 0, filename);

        if (width != -1 && height != -1) {
            image.scale(width, height);
        }

        this->screen.addStaticDrawable(&image);
    }
}

void StaticImageDisplay::show(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {
    canvas->Clear();
    this->screen.draw(canvas);
    matrix.SwapOnVSync(canvas);

    for (int i = 0; i < 10 && !interrupt_received; i++) {
        usleep(500000);
    }
}

void StaticImageDisplay::show_indefinitely(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {
    canvas->Clear();
    this->screen.draw(canvas);
    matrix.SwapOnVSync(canvas);

    while (!interrupt_received) {
        usleep(500000);
    }
}
