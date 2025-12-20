#ifndef CHRISTMASCOUNTDOWN_SCROLLINGIMAGEDISPLAY_H
#define CHRISTMASCOUNTDOWN_SCROLLINGIMAGEDISPLAY_H

#include "Display.h"

class ScrollingImageDisplay : public Display {
public:

    void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
    void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;

private:

    rgb_matrix::Font font;

};

#endif //CHRISTMASCOUNTDOWN_SCROLLINGIMAGEDISPLAY_H