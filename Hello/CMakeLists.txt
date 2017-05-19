cmake_minimum_required(VERSION 3.0.2)
project(Hello)

set(CMAKE_PREFIX_PATH "d:\\Qt\\Qt5.7.1\\5.7\\msvc2015_64\\")

find_package(Qt5Widgets)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(mainwindow mainwindow.cpp)
target_link_libraries (mainwindow Qt5::Widgets)

add_executable(hello main.cpp)
# target_link_libraries (hello mainwindow)
qt5_use_modules(hello Widgets)
qt5_use_modules(hello Core)