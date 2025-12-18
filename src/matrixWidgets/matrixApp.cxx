#include <matrixApp.h>
#include <ostream>
#include <iostream>
volatile sig_atomic_t MatrixApp::interrupt_received = 0;

void MatrixApp::InterruptHandler(int signo)
{
    (void)signo;
    interrupt_received = 1;
}

void MatrixApp::tick()
{
    _rootWidget->render(_canvas);
}

void MatrixApp::run()
{
    while (!interrupt_received) 
    {
        rgb_matrix::Color bg_color(0, 0, 0);

        _canvas->Fill(bg_color.r, bg_color.g, bg_color.b);

        // Sample current system time and convert to local broken-down time.
        struct timespec now;
        clock_gettime(CLOCK_REALTIME, &now);
        localtime_r(&now.tv_sec, &tm);

        tick();

        //Compute absolute next-second time to sleep until (align to whole seconds).
        next_time = now;
        //next_time.tv_sec += 1;
        next_time.tv_sec += 0;
        next_time.tv_nsec = 500;

        clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next_time, NULL);

        // Atomic swap with double buffer
        _canvas = _matrix->SwapOnVSync(_canvas);
   }

}