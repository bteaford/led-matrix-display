#ifndef MATRIXDISPLAY_IMAGE_H
#define MATRIXDISPLAY_IMAGE_H

#include <string>
#include <Magick++.h>

#include "Drawable.h"

class Image  : public Drawable {
public:
    Image(int x, int y, const std::string& fileNameParam);
    int height() override;
    int width() override;
    void draw(rgb_matrix::Canvas* canvas) override;
    void scale(int width, int height);

private:
    Magick::Image image;
};


#endif //MATRIXDISPLAY_IMAGE_H