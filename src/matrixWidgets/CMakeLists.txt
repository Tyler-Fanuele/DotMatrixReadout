cmake_minimum_required(VERSION 3.16)

add_library(MatrixWidgets OBJECT matrixDrawable.cxx matrixWidget.cxx)
target_include_directories(MatrixWidgets PUBLIC
  ${PROJECT_SOURCE_DIR}/include/matrixWidgets
)
target_compile_features(MatrixWidgets PUBLIC cxx_std_20)