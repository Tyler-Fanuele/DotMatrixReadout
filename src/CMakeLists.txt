cmake_minimum_required(VERSION 3.16)

add_subdirectory(matrixWidgets)     # source

include_directories(/usr/include/GraphicsMagick)

message(STATUS "Adding GraphicsMagick library")
add_library( GraphicsMagick SHARED IMPORTED )
set_target_properties(
    GraphicsMagick PROPERTIES IMPORTED_LOCATION 
    /usr/lib/libGraphicsMagick++.so
)

message(STATUS "Adding rpi-rgb-led-matrix library")
add_library( RpiRgbLedMatrix SHARED IMPORTED )
set_target_properties(
    RpiRgbLedMatrix PROPERTIES IMPORTED_LOCATION 
    /home/tfanuele/DotMatrixReadout/lib/rpi-rgb-led-matrix/lib/librgbmatrix.so.1
)

# If the custom target to build the rpi lib exists, ensure the imported target
# and the final executable depend on it so the library is built first.
if(TARGET build_rpi_rgb_matrix)
  add_dependencies(RpiRgbLedMatrix build_rpi_rgb_matrix)
endif()


add_executable(display main.cxx)
target_compile_features(display PUBLIC cxx_std_20)
target_link_libraries(
    display 
    MatrixWidgets 
    GraphicsMagick 
    RpiRgbLedMatrix
)
set_target_properties(display PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)