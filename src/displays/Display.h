#ifndef CHRISTMASCOUNTDOWN_DISPLAY_H
#define CHRISTMASCOUNTDOWN_DISPLAY_H

#include <MatrixOperations.h>

class Display {
public:
    virtual void load();
    virtual void show(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) = 0;
    virtual void show_indefinitely(rgb_matrix::RGBMatrix& matrix, rgb_matrix::FrameCanvas* canvas, volatile bool& interrupt_received) = 0;
    virtual ~Display();

    Display() = default;
};

#endif //CHRISTMASCOUNTDOWN_DISPLAY_H