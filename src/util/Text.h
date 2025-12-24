#ifndef MATRIXDISPLAY_TEXT_H
#define MATRIXDISPLAY_TEXT_H
#include <string>

#include "Drawable.h"
#include "graphics.h"


class Text : public Drawable {
public:
    Text(int x, int y, const std::string& text_param, rgb_matrix::Font* font_param, rgb_matrix::Color color_param);
    std::string getText();
    void setText(const std::string &text_param);
    rgb_matrix::Color getColor() const;
    void setColor(rgb_matrix::Color color_param);
    rgb_matrix::Font* getFont() const;
    void setFont(rgb_matrix::Font* font_param);
    int height() override;
    int width() override;
    void draw(rgb_matrix::Canvas* canvas) override;

private:
    std::string text;
    rgb_matrix::Font* font;
    rgb_matrix::Color color;
};


#endif //MATRIXDISPLAY_TEXT_H