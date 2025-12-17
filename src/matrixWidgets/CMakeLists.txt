cmake_minimum_required(VERSION 3.16)

set(SOURCE_FILES matrixDrawable.cxx matrixWidget.cxx)

add_library(MatrixWidgets ${SOURCE_FILES})

set_target_properties(MatrixWidgets PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    )

target_include_directories(MatrixWidgets PUBLIC
  ${CMAKE_SOURCE_DIR}/include/matrixWidgets
)
target_compile_features(MatrixWidgets PUBLIC cxx_std_20)
