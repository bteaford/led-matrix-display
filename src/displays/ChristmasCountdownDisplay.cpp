#include <unistd.h>

#include "ChristmasCountdownDisplay.h"
#include "Text.h"

ChristmasCountdownDisplay::ChristmasCountdownDisplay() :
screen(Screen(0, 0)),
days_label(Text(0, 0, "Days", &font, rgb_matrix::Color(0, 255, 0))),
num_of_days(Text(0, 0, "", &font, rgb_matrix::Color(0, 255, 0))),
hours_label(Text(0, 0, "Hours", &font, rgb_matrix::Color(255, 0, 0))),
num_of_hours(Text(0, 0, "", &font, rgb_matrix::Color(255, 0, 0))),
minutes_label(Text(0, 0, "Minutes", &font, rgb_matrix::Color(0, 255, 0))),
num_of_minutes(Text(0, 0, "", &font, rgb_matrix::Color(0, 255, 0))),
seconds_label(Text(0, 0, "Seconds", &font, rgb_matrix::Color(255, 0, 0))),
num_of_seconds(Text(0, 0, "", &font, rgb_matrix::Color(255, 0, 0)))
{}

void ChristmasCountdownDisplay::load() {
    font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");
    num_of_days.setFont(&font);
    num_of_hours.setFont(&font);
    num_of_minutes.setFont(&font);
    num_of_seconds.setFont(&font);

    num_of_days.setY(font.baseline());
    num_of_hours.setY(font.baseline() * 2);
    num_of_minutes.setY(font.baseline() * 3);
    num_of_seconds.setY(font.baseline() * 4);

    days_label = Text(0, font.baseline(), "Days", &font, rgb_matrix::Color(0, 255, 0));
    hours_label = Text(0, font.baseline() * 2, "Hours", &font, rgb_matrix::Color(255, 0, 0));
    minutes_label = Text(0, font.baseline() * 3, "Minutes", &font, rgb_matrix::Color(0, 255, 0));
    seconds_label = Text(0, font.baseline() * 4, "Seconds", &font, rgb_matrix::Color(255, 0, 0));

    days_label.setY(font.baseline());
    hours_label.setY(font.baseline() * 2);
    minutes_label.setY(font.baseline() * 3);
    seconds_label.setY(font.baseline() * 4);

    screen.addStaticDrawable(&days_label);
    screen.addStaticDrawable(&num_of_days);
    screen.addStaticDrawable(&hours_label);
    screen.addStaticDrawable(&num_of_hours);
    screen.addStaticDrawable(&minutes_label);
    screen.addStaticDrawable(&num_of_minutes);
    screen.addStaticDrawable(&seconds_label);
    screen.addStaticDrawable(&num_of_seconds);
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
        Text(0, (canvas->height() / 4) + (font.height() / 2), "It's", &font, rgb_matrix::Color(255, 0, 0)).draw(canvas);
        Text(0, (canvas->height() * 3 / 4) + (font.height() / 2), "Christmas", &font, rgb_matrix::Color(0, 255, 0)).draw(canvas);
    } else {
        const int num_hours = 23 - ti->tm_hour;
        const int num_min = 59 - ti->tm_min;
        const int num_sec = 59 - ti->tm_sec;

        num_of_days.setText(std::to_string(num_days < 0 ? 358 + (6 + num_days) : num_days));
        num_of_days.setX(canvas->width() - num_of_days.width());
        num_of_hours.setText(std::to_string(num_hours));
        num_of_hours.setX(canvas->width() - num_of_hours.width());
        num_of_minutes.setText(std::to_string(num_min));
        num_of_minutes.setX(canvas->width() - num_of_minutes.width());
        num_of_seconds.setText(std::to_string(num_sec));
        num_of_seconds.setX(canvas->width() - num_of_seconds.width());

        screen.draw(canvas);
    }
}

bool ChristmasCountdownDisplay::isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
