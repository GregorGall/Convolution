cmake_minimum_required(VERSION 3.0)
project(Convolution)
set(CMAKE_CXX_STANDART 17)

add_subdirectory(./LabSource)
add_subdirectory(./ConsoleGraph)
add_executable(main ./source/main.cpp)
target_link_libraries(main LabSource ConsoleGraph)
