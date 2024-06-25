cmake_minimum_required(VERSION 3.20)
project(cvpuzz)

set(CMAKE_CXX_STANDARD 26)

set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")

set(OpenCV_LIB "C:/opencv/build")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV REQUIRED)
include_directories(( ${OpenCV_INCLUDE_DIRS}))


set(CMAKE_PREFIX_PATH "C:/opencv/")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(cvpuzz PRIVATE ${OpenCV_LIBS})