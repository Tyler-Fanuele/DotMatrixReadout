#pragma once

#include <matrixDrawable.h>

class MatrixWidget : public MatrixDrawable{
    public:
    MatrixWidget(MatrixWidget* parent = nullptr)
    {
        if (parent != nullptr)
        {
            parent->addChild(this);
        }
    }

    ~MatrixWidget()
    {
        for (MatrixWidget*  each : _children)
        {
            delete each;
        }
        _children.clear();
    }

    virtual void draw(rgb_matrix::FrameCanvas* canvas) override
    {
        if (_show == true)
        {
            render(canvas);
        }
    }

    virtual bool render(rgb_matrix::FrameCanvas* canvas) = 0;

    bool getShow() { return _show;}
    void show() {_show = true;}
    void hide() {_show = false;}

    

    private:

    void addChild(MatrixWidget* parent) { _children.push_back(parent); }

    bool _show = true;

    std::vector<MatrixWidget*> _children;
};