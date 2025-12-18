#include <matrixDrawable.h>

class MatrixWidget : public MatrixDrawable{
    public:
    // MatrixWidget(MatrixWidget* parent)
    // {
    //     this->MatrixDrawable(parent->canvas());
    //     parent->addChild(this);
        
    // }
    MatrixWidget(rgb_matrix::FrameCanvas* canvas) : MatrixDrawable(canvas){}

    ~MatrixWidget()
    {
        for (MatrixWidget*  each : _children)
        {
            delete each;
        }
    }

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

    void addChild(MatrixWidget* parent) { _children.push_back(parent); }

    private:
    bool _show = true;

    std::vector<MatrixWidget*> _children;
};