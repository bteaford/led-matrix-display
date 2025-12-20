#ifndef CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H
#define CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H
#include <unistd.h>

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
    static int getWidthOfInt(int value, const rgb_matrix::Font *font);
    static void drawLine(int value, const rgb_matrix::Font &font, const std::string &line, rgb_matrix::Canvas *canvas, const rgb_matrix::Color &color, int line_scalar);

    struct DrawConfig {
        int value;
        std::string unit;
        rgb_matrix::Color color;
    };
};

#endif //CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H