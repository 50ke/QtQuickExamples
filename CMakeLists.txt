cmake_minimum_required(VERSION 3.16)

project(QtQuickExamples VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(PointCloudVisualizationQuick3D)
add_subdirectory(PointCloudVisualizationVtk)