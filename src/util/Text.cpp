#include "Text.h"

Text::Text(const int x, const int y, const std::string &text_param, rgb_matrix::Font* font_param, const rgb_matrix::Color color_param)
: Drawable(x, y) {
    this->text = text_param;
    this->color = color_param;
    this->font = font_param;
}

int Text::height() {
    return font->height();
}

int Text::width() {
    int sum = 0;
    for (const char c : text) {
        sum += font->CharacterWidth(static_cast<uint32_t>(c));
    }
    return sum;
}

void Text::draw(rgb_matrix::Canvas* canvas) {
    rgb_matrix::DrawText(canvas, *font, getX(), getY(), color, nullptr, text.c_str());
}

