#ifndef MATRIXDISPLAY_NCAAFSCOREDISPLAY_H
#define MATRIXDISPLAY_NCAAFSCOREDISPLAY_H

#include "Display.h"

class NCAAFScoreDisplay : public Display {
public:
    void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
    void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
private:
    rgb_matrix::Font font;
};


#endif //MATRIXDISPLAY_NCAAFSCOREDISPLAY_H