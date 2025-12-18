#pragma once

#include <matrixWidget.h>

class MatrixTextWidget : public MatrixWidget
{
    public:
        MatrixTextWidget(MatrixWidget* parent = nullptr)
            : MatrixWidget(parent), _letterSpacing(0), _color(255,255,0), _font(), _outlinedFont(NULL)
        {
                setXOffset(0);
                setYOffset(0);
        }

    ~MatrixTextWidget()
    {
        delete _outlinedFont;
    }

    bool tick() override {return true;}
    bool render(rgb_matrix::FrameCanvas* canvas) override;

    bool setFont(std::string fontFile);
    const rgb_matrix::Font& font() {return _font;}

    void setLetterSpacing(int letterSpacing) { _letterSpacing = letterSpacing; } 
    int letterSpacing(void) const { return _letterSpacing; }

    void setText(std::string text) { _text = text; }
    std::string text() { return _text; }

    void setColor(rgb_matrix::Color color) {_color = color; }
    void setColor(int r, int g, int b) {_color = rgb_matrix::Color(r, g, b); }
    rgb_matrix::Color& color() { return _color; }

    protected:
    
    std::string _text;

    int _letterSpacing;

    rgb_matrix::Color _color;

    rgb_matrix::Font _font;
    rgb_matrix::Font* _outlinedFont;
};