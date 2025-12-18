#pragma once

#include <led-matrix.h>
#include <graphics.h>

class MatrixDrawable 
{
    public:
    MatrixDrawable(){}

    virtual void draw(rgb_matrix::FrameCanvas* canvas) = 0;

    void setXOffset(int xOffset) { _xOffset = xOffset; }
    int xOffset(void) const { return _xOffset; }

    void setYOffset(int yOffset) { _yOffset = yOffset; }
    int yOffset(void) const { return _yOffset; }

    protected:
    int _xOffset;
    int _yOffset;
};