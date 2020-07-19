cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(camera_fusion)

find_package(OpenCV 4.1 REQUIRED)

# add matplotlibcpp
# 1. find_package()
# 2. add python include dirs to include_directories()
# 3. add python libs to target_link_libraries()
find_package(PythonLibs 2.7)

include_directories(${OpenCV_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Executable for create matrix exercise
add_executable (2D_feature_tracking src/matching2D_Student.cpp src/MidTermProject_Camera_Student.cpp src/mycvtools.cpp src/properties.cpp)
target_link_libraries (2D_feature_tracking ${OpenCV_LIBRARIES} ${PYTHON_LIBRARIES})