#include <matrixTextWidget.h>

bool MatrixTextWidget::render(rgb_matrix::FrameCanvas* canvas)
{
    rgb_matrix::DrawText(canvas, _font,
                           _xOffset, _yOffset,
                           _color, NULL, _text.c_str(),
                           _letterSpacing);
    return true;
}

bool MatrixTextWidget::setFont(std::string fontFile)
{
    if (!_font.LoadFont(fontFile.c_str())) {
        fprintf(stderr, "Couldn't load font '%s'\n", fontFile.c_str());
        return false;
    }
    
    _outlinedFont = _font.CreateOutlineFont();

    return true;
}