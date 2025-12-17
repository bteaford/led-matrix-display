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
  PrintMatrixFlags(stderr);
  return 1;
}

int getWidthOfInt(const int value, const Font *font) {
    const std::string s = std::to_string(value);
    int sum = 0;
    for (const char c : s) {
        sum += font->CharacterWidth(static_cast<uint32_t>(c));
    }
    return sum;
}


struct DrawConfig {
    int value;
    std::string unit;
    Color color;
};

void drawLine(const int value, const Font &font, const std::string &line, Canvas *canvas, const Color &color, const int line_scalar) {
    const std::string s = std::to_string(value);

    DrawText(canvas, font, 0, font.baseline() * line_scalar, color, nullptr, line.c_str());
    DrawText(canvas, font, canvas->width() - getWidthOfInt(value, &font), font.baseline() * line_scalar, color, nullptr, s.c_str());
}

int main(int argc, char *argv[]) {

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    RGBMatrix::Options matrix_options;
    RuntimeOptions runtime_opt;
    if (!ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
        return usage(argv[0]);
    }

    matrix_options.brightness = 10;
    matrix_options.cols = 64;
    matrix_options.hardware_mapping = "adafruit-hat";

    const Color green(0, 255, 0);
    const Color red(255, 0, 0);

    Font font;
    if (!font.LoadFont("/home/rpi/projects/led-matrix-display/lib/rpi-rgb-led-matrix/fonts/6x10.bdf")) {
        fprintf(stderr, "font load failed");
        return 1;
    }
    RGBMatrix *canvas = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
    if (canvas == nullptr) {
        fprintf(stderr, "canvas was nullptr");
        return 1;
    }

    FrameCanvas *offscreen_canvas = canvas->CreateFrameCanvas();


    while(!interrupt_received) {
        offscreen_canvas->Clear();

        // Declaring argument for time()
        time_t tt;

        // Applying time()
        time(&tt);

        // Using localtime()
        const tm *ti = localtime(&tt);

        const int num_days = 357 - ti->tm_yday;
        const int num_hours = 23 - ti->tm_hour;
        const int num_min = 59 - ti->tm_min;
        const int num_sec = 59 - ti->tm_sec;

        if (num_days == -1) {
            int y1 = (offscreen_canvas->height() / 4) + (font.height() / 2);
            int y2 = (offscreen_canvas->height() * 3 / 4) + (font.height() / 2);
            DrawText(offscreen_canvas, font, 0, y1, red, nullptr, "It's");
            DrawText(offscreen_canvas, font, 0, y2, green, nullptr, "Christmas!");
        } else {
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

            int i = 1;
            for (const auto &[value, unit, color] : draw_configs) {
                drawLine(value, font, unit, offscreen_canvas, color, i);
                i++;
            }
        }

        offscreen_canvas = canvas->SwapOnVSync(offscreen_canvas);

        usleep(500000);
    }

    delete canvas;

    return 0;

}