#ifndef MATRIXDISPLAY_STATICIMAGEDISPLAY_H
#define MATRIXDISPLAY_STATICIMAGEDISPLAY_H
#include "Display.h"
#include "Image.h"
#include "Screen.h"

class StaticImageDisplay : public Display{
public:
    StaticImageDisplay(int argc, char *argv[]);
    void load() override;
    void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
    void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;

private:
    Screen screen;
    int argc;
    char **argv;
};

#endif //MATRIXDISPLAY_STATICIMAGEDISPLAY_H