#include <unistd.h>

#include "ChristmasCountdownDisplay.h"

void ChristmasCountdownDisplay::load() {
    green = rgb_matrix::Color(0, 255, 0);
    red = rgb_matrix::Color(255, 0, 0);
    font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf");
}

void ChristmasCountdownDisplay::show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) {
    for (int i = 0; i < 10 && !interrupt_received; i++) {
        canvas->Clear();
        time_t tt;
        time(&tt);
        const tm *ti = localtime(&tt);

        const int num_days = (isLeapYear(ti->tm_year) ? 358 : 357) - ti->tm_yday;

        if (num_days == -1) {
            const int y1 = (canvas->height() / 4) + (font.height() / 2);
            const int y2 = (canvas->height() * 3 / 4) + (font.height() / 2);
            rgb_matrix::DrawText(canvas, font, 0, y1, red, nullptr, "It's");
            rgb_matrix::DrawText(canvas, font, 0, y2, green, nullptr, "Christmas!");
        } else {
            const int num_hours = 23 - ti->tm_hour;
            const int num_min = 59 - ti->tm_min;
            const int num_sec = 59 - ti->tm_sec;

            const std::string first_line = "Days";
            const std::string second_line = "Hours";
            const std::string third_line = "Minutes";
            const std::string fourth_line = "Seconds";

            std::vector<DrawConfig> draw_configs = {
                {num_days < 0 ? 358 + (6 + num_days) : num_days, first_line, green},
                {num_hours, second_line, red},
                {num_min, third_line, green},
                {num_sec, fourth_line, red}
            };

            int j = 1;
            for (const auto &[value, unit, color] : draw_configs) {
                drawLine(value, font, unit, canvas, color, j);
                j++;
            }
        }
        canvas = matrix.SwapOnVSync(canvas);
        usleep(500000);
    }
}

void ChristmasCountdownDisplay::show_indefinitely(rgb_matrix::RGBMatrix &matrix, rgb_matrix::FrameCanvas *canvas, volatile bool &interrupt_received) {
    while (!interrupt_received) {
        canvas->Clear();
        time_t tt;
        time(&tt);
        const tm *ti = localtime(&tt);

        const int num_days = (isLeapYear(ti->tm_year) ? 358 : 357) - ti->tm_yday;

        if (num_days == -1) {
            const int y1 = (canvas->height() / 4) + (font.height() / 2);
            const int y2 = (canvas->height() * 3 / 4) + (font.height() / 2);
            rgb_matrix::DrawText(canvas, font, 0, y1, red, nullptr, "It's");
            rgb_matrix::DrawText(canvas, font, 0, y2, green, nullptr, "Christmas!");
        } else {
            const int num_hours = 23 - ti->tm_hour;
            const int num_min = 59 - ti->tm_min;
            const int num_sec = 59 - ti->tm_sec;

            const std::string first_line = "Days";
            const std::string second_line = "Hours";
            const std::string third_line = "Minutes";
            const std::string fourth_line = "Seconds";

            std::vector<DrawConfig> draw_configs = {
                {num_days < 0 ? 358 + (6 + num_days) : num_days, first_line, green},
                {num_hours, second_line, red},
                {num_min, third_line, green},
                {num_sec, fourth_line, red}
            };

            int j = 1;
            for (const auto &[value, unit, color] : draw_configs) {
                drawLine(value, font, unit, canvas, color, j);
                j++;
            }
        }
        canvas = matrix.SwapOnVSync(canvas);
        usleep(500000);
    }
}

bool ChristmasCountdownDisplay::isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int ChristmasCountdownDisplay::getWidthOfInt(const int value, const rgb_matrix::Font *font) {
    const std::string s = std::to_string(value);
    int sum = 0;
    for (const char c : s) {
        sum += font->CharacterWidth(static_cast<uint32_t>(c));
    }
    return sum;
}

void ChristmasCountdownDisplay::drawLine(const int value, const rgb_matrix::Font &font, const std::string &line, rgb_matrix::Canvas *canvas, const rgb_matrix::Color &color, const int line_scalar) {
    const std::string s = std::to_string(value);

    DrawText(canvas, font, 0, font.baseline() * line_scalar, color, nullptr, line.c_str());
    DrawText(canvas, font, canvas->width() - getWidthOfInt(value, &font), font.baseline() * line_scalar, color, nullptr, s.c_str());
}
