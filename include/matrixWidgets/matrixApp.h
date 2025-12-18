#pragma once

#include <matrixWidget.h>
#include <stdexcept>

#include <signal.h>

class MatrixApp 
{
    public:
    MatrixApp(int argc, char** argv)
    {
        rgb_matrix::RGBMatrix::Options matrix_options;
        rgb_matrix::RuntimeOptions runtime_opt;



        if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt)) 
        {
            throw std::runtime_error("Parse command line did not work");
        }

        _matrix = rgb_matrix::RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
        if (_matrix == NULL)
        {
            throw std::runtime_error("matrix pointer returned NULL");
        }

        _canvas = _matrix->CreateFrameCanvas();

        //_matrix->SetPWMBits(1);

        interrupt_received = 0;

        signal(SIGTERM, InterruptHandler);
        signal(SIGINT, InterruptHandler);
    }

    ~MatrixApp()
    {
        if (_rootWidget)
        {
            delete _rootWidget;
        }
        delete _matrix;
        signal(SIGTERM, SIG_DFL);
        signal(SIGINT, SIG_DFL);
    }

    void tick();
    void run();

    void setRootWidget(MatrixWidget* rootWidget) 
    {
        _rootWidget = rootWidget;
    }
    MatrixWidget* rootWidget() {return _rootWidget;}

    private:

    static volatile sig_atomic_t interrupt_received;
    static void InterruptHandler(int signo);

    struct timespec next_time;
    struct tm tm;


    MatrixWidget* _rootWidget;

    rgb_matrix::RGBMatrix* _matrix;
    rgb_matrix::FrameCanvas* _canvas;
};
