#include <matrixTextWidget.h>

bool MatrixTextWidget::render(void)
{
    
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