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

    void draw(rgb_matrix::FrameCanvas* canvas) final override
    {
        if (_show == true)
        {
            tick();
            render(canvas);
        }
        for (auto childWidget : _children)
        {
            if (childWidget)
            {
                childWidget->draw(canvas);
            }
            
        }
    }

    virtual bool tick() = 0;

    virtual bool render(rgb_matrix::FrameCanvas* canvas) = 0;

    bool getShow() { return _show;}
    void show() {_show = true;}
    void hide() {_show = false;}

    

    private:

    void addChild(MatrixWidget* parent) { _children.push_back(parent); }

    bool _show = true;

    std::vector<MatrixWidget*> _children;
};