//
// Created by Brad on 12/20/25.
//

#include "Drawable.h"

Drawable::Drawable(const int x, const int y) {
    this->x = x;
    this->y = y;
}

Drawable::~Drawable() = default;

int Drawable::getX() {
    return x;
}

void Drawable::setX(int x) {
    this->x = x;
}

int Drawable::getY() {
    return y;
}

void Drawable::setY(int y) {
    this->y = y;
}

bool Drawable::isOffScreen(int canvasWidth, int canvasHeight) {
    return this->x >= canvasWidth ||
        this->y >= canvasHeight ||
            this->x + width() <= 0 ||
                this->y + height() <= 0;
}