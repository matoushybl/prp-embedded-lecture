cmake_minimum_required(VERSION 3.19)
project(prp_lecture_embedded)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(libs)
include_directories(include)
add_library(project_shared STATIC src/UDPSocket.cpp src/Robot.cpp)
target_link_libraries(project_shared spdlog)

add_executable(prp_lecture_embedded src/main.cpp)
target_link_libraries(prp_lecture_embedded project_shared)

add_subdirectory(test)