#include <unistd.h>

#include "ChristmasCountdownDisplay.h"
#include "Text.h"

void ChristmasCountdownDisplay::load() {
    green = rgb_matrix::Color(0, 255, 0);
    red = rgb_matrix::Color(255, 0, 0);
    font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");
}

void ChristmasCountdownDisplay::show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) {
    for (int i = 0; i < 10 && !interrupt_received; i++) {
        drawCountdown(matrix, canvas);
        canvas = matrix.SwapOnVSync(canvas);
        usleep(500000);
    }
}

void ChristmasCountdownDisplay::show_indefinitely(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {
    while (!interrupt_received) {
        drawCountdown(matrix, canvas);
        canvas = matrix.SwapOnVSync(canvas);
        usleep(500000);
    }
}

void ChristmasCountdownDisplay::drawCountdown(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas) {
    canvas->Clear();
    time_t tt;
    time(&tt);
    const tm *ti = localtime(&tt);

    if (const int num_days = (isLeapYear(ti->tm_year) ? 358 : 357) - ti->tm_yday; num_days == -1) {
        Text(0, (canvas->height() / 4) + (font.height() / 2), "It's", &font, red).draw(canvas);
        Text(0, (canvas->height() * 3 / 4) + (font.height() / 2), "Christmas", &font, green).draw(canvas);
    } else {
        const int num_hours = 23 - ti->tm_hour;
        const int num_min = 59 - ti->tm_min;
        const int num_sec = 59 - ti->tm_sec;

        Text(0, font.baseline(), "Days", &font, green).draw(canvas);
        Text(0, font.baseline() * 2, "Hours", &font, red).draw(canvas);
        Text(0, font.baseline() * 3, "Minutes", &font, green).draw(canvas);
        Text(0, font.baseline() * 4, "Seconds", &font, red).draw(canvas);

        auto days = Text(0, font.baseline(), std::to_string(num_days < 0 ? 358 + (6 + num_days) : num_days), &font, green);
        days.setX(canvas->width() - days.width());
        auto hours = Text(0, font.baseline() * 2, std::to_string(num_hours), &font, red);
        hours.setX(canvas->width() - hours.width());
        auto minutes = Text(0, font.baseline() * 3, std::to_string(num_min), &font, green);
        minutes.setX(canvas->width() - minutes.width());
        auto seconds = Text(0, font.baseline() * 4, std::to_string(num_sec), &font, red);
        seconds.setX(canvas->width() - seconds.width());

        days.draw(canvas);
        hours.draw(canvas);
        minutes.draw(canvas);
        seconds.draw(canvas);
    }
}

bool ChristmasCountdownDisplay::isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
