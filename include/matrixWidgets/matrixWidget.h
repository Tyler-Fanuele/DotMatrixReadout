#include <matrixDrawable.h>

class MatrixWidget : public MatrixDrawable{
    public:
    MatrixWidget(rgb_matrix::FrameCanvas* canvas) : MatrixDrawable(canvas){}

    virtual void draw(void) override
    {
        if (_show == true)
        {
            render();
        }
    }

    virtual bool render(void) = 0;

    bool getShow() { return _show;}
    void show() {_show = true;}
    void hide() {_show = false;}

    private:
    bool _show = true;
};