#include <matrixWidget.h>

void MatrixWidget::draw(rgb_matrix::FrameCanvas* canvas)
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
