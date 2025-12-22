#ifndef CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H
#define CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H

#include "Display.h"

class ChristmasCountdownDisplay : public Display {
public:
    void load() override;
    void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
    void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;

private:
    rgb_matrix::Color green;
    rgb_matrix::Color red;
    rgb_matrix::Font font;

    static bool isLeapYear(int year);
    void drawCountdown(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas);

    struct DrawConfig {
        int value;
        std::string unit;
        rgb_matrix::Color color;
    };
};

#endif //CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H