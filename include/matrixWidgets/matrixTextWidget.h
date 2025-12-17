#include <matrixWidget.h>

class MatrixTextWidget : public MatrixWidget
{
    public:
    MatrixTextWidget(rgb_matrix::FrameCanvas* canvas) : MatrixWidget(canvas) 
    {
        _outlinedFont = NULL;
    }

    ~MatrixTextWidget()
    {
        delete _outlinedFont;
    }

    bool render(void) override;

    bool setFont(std::string fontFile);

    void setLetterSpacing(int letterSpacing) { _letterSpacing = letterSpacing; } 
    int letterSpacing(void) const { return _letterSpacing; }

    void setText(std::string text) { _text = text; }
    std::string text() { return _text; }

    protected:
    
    std::string _text;

    int _letterSpacing;

    rgb_matrix::Font _font;
    rgb_matrix::Font* _outlinedFont;
};