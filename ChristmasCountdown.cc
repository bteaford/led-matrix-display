#include "led-matrix.h"
#include "graphics.h"

#include <signal.h>
#include <sstream>
#include <string>

using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static int usage(const char *progname) {
  fprintf(stderr, "usage: %s [options]\n", progname);
  rgb_matrix::PrintMatrixFlags(stderr);
  return 1;
}

int getWidthOfInt(int value, Font *font) {
    // Convert number to string
    std::string s = std::to_string(value);

    // Convert each digit to Unicode (uint32_t)
    std::vector<uint32_t> unicode;
    for (char c : s) {
        unicode.push_back(static_cast<uint32_t>(c));
    }

    int sum = 0;
    for(uint32_t digit : unicode) {
        sum += font->CharacterWidth(digit);
    }

    return sum;
}

int main(int argc, char *argv[]) {

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
        return usage(argv[0]);
    }

    Color green(0, 255, 0);
    Color red(255, 0, 0);
    Color blue(0, 0, 255);
    Color white(255, 255, 255);

    int letter_spacing = 0;

    rgb_matrix::Font font;
    if (!font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf")) {
        fprintf(stderr, "font load failed");
        return 1;
    }
    RGBMatrix *canvas = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
    if (canvas == NULL) {
        fprintf(stderr, "canvas was NULL");
        return 1;
    }

    FrameCanvas *offscreen_canvas = canvas->CreateFrameCanvas();


    while(!interrupt_received) {

        offscreen_canvas->Clear();

        // Declaring argument for time()
        time_t tt;

        // Declaring variable to store return value of
        // localtime()
        struct tm* ti;

        // Applying time()
        time(&tt);

        // Using localtime()
        ti = localtime(&tt);

        std::stringstream day_stream;
        std::stringstream hour_stream;
        std::stringstream min_stream;
        std::stringstream sec_stream;

        int num_days = 24 - ti->tm_mday;
        int num_hours = 23 - ti->tm_hour;
        int num_min = 59 - ti->tm_min;
        int num_sec = 59 - ti->tm_sec;

        day_stream << 24 - ti->tm_mday;
        std::string days = day_stream.str();
        hour_stream << 23 - ti->tm_hour;
        std::string hours = hour_stream.str();
        min_stream << 59 - ti->tm_min;
        std::string minutes = min_stream.str();
        sec_stream << 59 - ti->tm_sec;
        std::string seconds = sec_stream.str();


        std::string first_line = "Days";
        std::string second_line = "Hours";
        std::string third_line = "Minutes";
        std::string fourth_line = "Seconds";
        rgb_matrix::DrawText(offscreen_canvas, font, 0, font.baseline(), green, NULL, first_line.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, offscreen_canvas->width() - getWidthOfInt(num_days, &font), font.baseline(), green, NULL, days.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, 0, font.baseline() * 2, red, NULL, second_line.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, offscreen_canvas->width() - getWidthOfInt(num_hours, &font), font.baseline() * 2, red, NULL, hours.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, 0, font.baseline() * 3, green, NULL, third_line.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, offscreen_canvas->width() - getWidthOfInt(num_min, &font), font.baseline() * 3, green, NULL, minutes.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, 0, font.baseline() * 4, red, NULL, fourth_line.c_str(), letter_spacing);
        rgb_matrix::DrawText(offscreen_canvas, font, offscreen_canvas->width() - getWidthOfInt(num_sec, &font), font.baseline() * 4, red, NULL, seconds.c_str(), letter_spacing);

        offscreen_canvas = canvas->SwapOnVSync(offscreen_canvas);

        usleep(500000);
    }

    delete canvas;

    return 0;

}