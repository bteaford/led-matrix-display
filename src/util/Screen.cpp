#include "Screen.h"

Screen::Screen(const int horizontalScrollDirection, const int verticalScrollDirection) {
    if (horizontalScrollDirection > 0) {
        this->horizontal_scroll_direction = 1;
    } else if (horizontalScrollDirection < 0) {
        this->horizontal_scroll_direction = -1;
    } else {
        this->horizontal_scroll_direction = 0;
    }

    if (verticalScrollDirection > 0) {
        this->vertical_scroll_direction = 1;
    } else if (verticalScrollDirection < 0) {
        this->vertical_scroll_direction = -1;
    } else {
        this->vertical_scroll_direction = 0;
    }

    this->leftmost_scrolling_drawable = nullptr;
    this->rightmost_scrolling_drawable = nullptr;
    this->highest_vertical_scrolling_drawable = nullptr;
    this->lowest_vertical_scrolling_drawable = nullptr;
}

void Screen::addStaticDrawable(std::unique_ptr<Drawable> drawable) {
    this->static_drawables.push_back(std::move(drawable));
}

void Screen::addScrollingDrawable(std::unique_ptr<Drawable> drawable) {
    this->scrolling_drawables.push_back(std::move(drawable));
    isNewScrollingDrawableExtreme(drawable);
}

Drawable* Screen::getStaticDrawable(const int pos) const {
    return static_drawables.at(pos).get();
}

Drawable* Screen::getScrollingDrawable(const int pos) const {
    return scrolling_drawables.at(pos).get();
}

void Screen::draw(rgb_matrix::Canvas *canvas) const {
    for (const auto & static_drawable : this->static_drawables) {
        static_drawable->draw(canvas);
    }

    for (const auto & scrolling_drawable : this->scrolling_drawables) {
        scrolling_drawable->draw(canvas);
    }
}

void Screen::scroll() const {
    for (const auto & scrolling_drawable : this->scrolling_drawables) {
        scrolling_drawable->setX(scrolling_drawable->getX() + this->horizontal_scroll_direction);
        scrolling_drawable->setY(scrolling_drawable->getY() + this->vertical_scroll_direction);
    }
}

void Screen::reset(const int canvasWidth, const int canvasHeight) const {
    int x_mod = 0, y_mod = 0;
    if (this->horizontal_scroll_direction != 0) {
        x_mod = rightmost_scrolling_drawable->getX() + rightmost_scrolling_drawable->width() - leftmost_scrolling_drawable->getX() + canvasWidth;
        x_mod *= -1;
    }
    if (this->vertical_scroll_direction != 0) {
        y_mod = rightmost_scrolling_drawable->getY() + rightmost_scrolling_drawable->height() - leftmost_scrolling_drawable->getY() + canvasHeight;
        y_mod *= -1;
    }

    for (const auto & scrolling_drawable : this->scrolling_drawables) {
        scrolling_drawable->setX(scrolling_drawable->getX() + x_mod);
        scrolling_drawable->setY(scrolling_drawable->getY() + y_mod);
    }
}

bool Screen::isScrolling() const {
    return this->horizontal_scroll_direction != 0 || this->vertical_scroll_direction != 0;
}

bool Screen::isScrollingComplete(const int canvasWidth, const int canvasHeight) const {
    const bool isHorizontalScrolling = this->horizontal_scroll_direction != 0;
    const bool isVerticalScrolling = this->vertical_scroll_direction != 0;
    const bool isHorizontalScrollingComplete = (horizontal_scroll_direction < 0 &&
        rightmost_scrolling_drawable != nullptr &&
        rightmost_scrolling_drawable->getX() + rightmost_scrolling_drawable->width() < 0) ||
            (horizontal_scroll_direction > 0 &&
                leftmost_scrolling_drawable != nullptr &&
                leftmost_scrolling_drawable->getX() > canvasWidth);
    const bool isVerticalScrollingComplete = (vertical_scroll_direction < 0 &&
        rightmost_scrolling_drawable != nullptr &&
        rightmost_scrolling_drawable->getY() + rightmost_scrolling_drawable->height() < 0) ||
            (vertical_scroll_direction > 0 &&
                leftmost_scrolling_drawable != nullptr &&
                leftmost_scrolling_drawable->getY() > canvasHeight);
    return (!isHorizontalScrolling || isHorizontalScrollingComplete) && (!isVerticalScrolling || isVerticalScrollingComplete);
}


void Screen::isNewScrollingDrawableExtreme(const std::unique_ptr<Drawable>& drawable) {
    if (rightmost_scrolling_drawable == nullptr ||
        (horizontal_scroll_direction < 0 && drawable->getX() + drawable->width() > rightmost_scrolling_drawable->getX() + rightmost_scrolling_drawable->width())) {
        rightmost_scrolling_drawable = drawable.get();
    }

    if (leftmost_scrolling_drawable == nullptr  ||
            (horizontal_scroll_direction > 0 && drawable->getX() < leftmost_scrolling_drawable->getX())) {
        leftmost_scrolling_drawable = drawable.get();
    }

    if (lowest_vertical_scrolling_drawable == nullptr ||
        (vertical_scroll_direction < 0 && drawable->getY() + drawable->height() > lowest_vertical_scrolling_drawable->getY() + lowest_vertical_scrolling_drawable->height())) {
        lowest_vertical_scrolling_drawable = drawable.get();
    }

    if (highest_vertical_scrolling_drawable == nullptr  ||
            (vertical_scroll_direction > 0 &&  drawable->getY() + drawable->height() < highest_vertical_scrolling_drawable->getY())) {
        highest_vertical_scrolling_drawable = drawable.get();
    }
}
