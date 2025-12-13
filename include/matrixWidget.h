#include "../include/matrixDrawable.h"

class MatrixWidget : public MatrixDrawable{
    MatrixWidget(int xOffset, int yOffset, rgb_matrix::FrameCanvas* canvas) : MatrixDrawable(xOffset, yOffset, canvas){}

    virtual bool draw(void) override; // returns false, will not draw anything
};