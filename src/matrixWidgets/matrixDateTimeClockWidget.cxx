#include <matrixDateTimeClockWidget.h>

bool MatrixDateTimeClockWidget::tick()
{
    char text_buffer[256];
    // Sample current system time and convert to local broken-down time.
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    localtime_r(&now.tv_sec, &tm);

    strftime(text_buffer, sizeof(text_buffer), std::string("%I:%M %p").c_str(), &tm);
    
    _clock->setText(text_buffer);

    strftime(text_buffer, sizeof(text_buffer), std::string("%a %D").c_str(), &tm);

    _date->setText(text_buffer);
    return true;
}

bool MatrixDateTimeClockWidget::render(rgb_matrix::FrameCanvas* canvas)
{


    return true;
}