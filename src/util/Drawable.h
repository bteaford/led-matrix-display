#ifndef MATRIXDISPLAY_DRAWABLE_H
#define MATRIXDISPLAY_DRAWABLE_H
#include "graphics.h"


class Drawable {
public:

    Drawable(int x, int y);
    virtual ~Drawable();
    virtual int getX();
    virtual int getY();
    virtual void setX(int x);
    virtual void setY(int y);
    virtual int height() = 0;
    virtual int width() = 0;
    virtual void draw(rgb_matrix::Canvas* canvas) = 0;
    virtual bool isOffScreen(int canvasWidth, int canvasHeight);

private:
    int x;
    int y;
};


#endif //MATRIXDISPLAY_DRAWABLE_H