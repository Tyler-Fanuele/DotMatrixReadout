#pragma once

#include <matrixTextWidget.h>
#include <matrixIconWidget.h>

class MatrixDateTimeClockWidget : public MatrixWidget
{
    public:

    MatrixDateTimeClockWidget(MatrixWidget* parent = nullptr) : 
    MatrixWidget(parent)
    {
        const char* FontDirectoryString = "./lib/rpi-rgb-led-matrix/fonts/";
        const char* LargeFontFileString = "7x14B.bdf";
        const char* SmallFontFileString = "tom-thumb.bdf";

        const std::string LargeFontString(std::string(FontDirectoryString) + std::string(LargeFontFileString));
        const std::string SmallFontString(std::string(FontDirectoryString) + std::string(SmallFontFileString));

        int centerTimeSpacing = 5;
        int centerDateSpacing = 2;

        int line_offset = 0;

        int letter_spacing = 0;
        int line_spacing = 9;

        const int x = 0;
        int y = 0;

        _clock = new MatrixTextWidget(this);

        _clock->setFont(LargeFontString.c_str());
        _clock->setColor(180,0,0);

        _clock->setXOffset(x + centerTimeSpacing);
        _clock->setYOffset(y + _clock->font().baseline() + line_offset);
        _clock->setLetterSpacing(letter_spacing);

        line_offset += _clock->font().height() + line_spacing;

        _date = new MatrixTextWidget(this);

        _date->setFont(SmallFontString.c_str());
        _date->setColor(180,0,0);

        _date->setXOffset(x + centerTimeSpacing);
        _date->setYOffset(y + _date->font().baseline() + line_offset);
        _date->setLetterSpacing(letter_spacing);

        _icon = new MatrixIconWidget(this);

        Magick::Image* img = new Magick::Image;
        const char* bitmapPath = "./assets/icons/Heart5x5.bmp";
        img->read(bitmapPath);              // path relative to cwd
        img->scale(Magick::Geometry(5, 5));  

        _icon->setIcon(img);

        _icon->setXOffset(56 + x);
        _icon->setYOffset(y  + line_offset);
    }

    bool render(rgb_matrix::FrameCanvas* canvas);

    private:

    struct timespec next_time;
    struct tm tm;

    MatrixTextWidget* _clock;
    MatrixTextWidget* _date;

    MatrixIconWidget* _icon;
    
};