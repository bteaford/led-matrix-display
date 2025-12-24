#ifndef CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H
#define CHRISTMASCOUNTDOWN_CHRISTMASCOUNTDOWNDISPLAY_H

#include "Display.h"
#include "Screen.h"
#include "Text.h"

class ChristmasCountdownDisplay : public Display {
public:
    ChristmasCountdownDisplay();
    void load() override;
    void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;
    void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) override;

private:
    Screen screen;
    Text days_label;
    Text num_of_days;
    Text hours_label;
    Text num_of_hours;
    Text minutes_label;
    Text num_of_minutes;
    Text seconds_label;
    Text num_of_seconds;
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