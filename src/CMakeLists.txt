cmake_minimum_required(VERSION 3.16)

add_subdirectory(matrixWidgets)     # source

include_directories(/usr/include/GraphicsMagick)

add_library( GraphicsMagick SHARED IMPORTED )
set_target_properties( GraphicsMagick PROPERTIES IMPORTED_LOCATION /usr/lib/libGraphicsMagick++.so)

add_library( RpiRgbLedMatrix SHARED IMPORTED )
set_target_properties( RpiRgbLedMatrix PROPERTIES IMPORTED_LOCATION /home/tfanuele/DotMatrixReadout/lib/rpi-rgb-led-matrix/lib/librgbmatrix.so.1)

add_executable(display main.cxx)
target_compile_features(display PUBLIC cxx_std_20)
target_link_libraries(display MatrixWidgets GraphicsMagick RpiRgbLedMatrix)
set_target_properties(display PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)