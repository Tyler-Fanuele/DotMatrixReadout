#pragma once

#include <matrixDrawable.h>
#include <matrixApp.h>

class MatrixWidget : public MatrixDrawable{
    public:
    MatrixWidget(MatrixWidget* parent = nullptr)
    {
        if (parent != nullptr)
        {
            parent->addChild(this);
            _app = &parent->app();
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

    void draw(rgb_matrix::FrameCanvas* canvas) final override;

    virtual bool tick() = 0;

    virtual bool render(rgb_matrix::FrameCanvas* canvas) = 0;

    bool getShow() { return _show;}
    void show() {_show = true;}
    void hide() {_show = false;}

    const MatrixApp& app() const { return *_app; }

    private:

    void addChild(MatrixWidget* child) { _children.push_back(child); }

    bool _show = true;

    std::vector<MatrixWidget*> _children;
    const MatrixApp* _app = nullptr;

};