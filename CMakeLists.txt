cmake_minimum_required(VERSION 3.16)

project(vision_homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(homework src/main.cpp)

target_include_directories(homework PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(homework PRIVATE ${OpenCV_LIBS})