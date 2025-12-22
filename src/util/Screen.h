#ifndef MATRIXDISPLAY_SCREEN_H
#define MATRIXDISPLAY_SCREEN_H
#include <memory>
#include <vector>

#include "Drawable.h"


class Screen {
public:
    Screen(int horizontalScrollDirection, int verticalScrollDirection);
    void addStaticDrawable(std::unique_ptr<Drawable> drawable);
    void addScrollingDrawable(std::unique_ptr<Drawable> drawable);
    [[nodiscard]] Drawable* getStaticDrawable(int pos) const;
    [[nodiscard]] Drawable* getScrollingDrawable(int pos) const;
    void draw(rgb_matrix::Canvas* canvas) const;
    void scroll() const;
    void reset(int canvasWidth, int canvasHeight) const;
    [[nodiscard]] bool isScrolling() const;
    [[nodiscard]] bool isScrollingComplete(int canvasWidth, int canvasHeight) const;

private:
    int horizontal_scroll_direction;
    int vertical_scroll_direction;
    Drawable* leftmost_scrolling_drawable;
    Drawable* rightmost_scrolling_drawable;
    Drawable* highest_vertical_scrolling_drawable;
    Drawable* lowest_vertical_scrolling_drawable;
    std::vector<std::unique_ptr<Drawable>> static_drawables;
    std::vector<std::unique_ptr<Drawable>> scrolling_drawables;

    void isNewScrollingDrawableExtreme(const std::unique_ptr<Drawable>& drawable);
};


#endif //MATRIXDISPLAY_SCREEN_H