#pragma once

#include <matrixWidget.h>
#include <Magick++.h>

class MatrixIconWidget : public MatrixWidget
{
    public:

    MatrixIconWidget(MatrixWidget* parent = nullptr) : 
    MatrixWidget(parent)
    {

    }

    ~MatrixIconWidget()
    {
        if (img)
        {
            delete img;
        }
    }

    bool render(rgb_matrix::FrameCanvas* canvas);

    void setIcon(Magick::Image* image) 
    {
        if (img != nullptr)
        {
            delete img;
        }
        img = image; 
    }
    const Magick::Image& icon() {return *img;}

    private:

    Magick::Image* img = nullptr;
};