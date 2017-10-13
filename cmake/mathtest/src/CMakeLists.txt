cmake_minimum_required(VERSION 3.4)

project(mathtest_prj)

include_directories(${PROJECT_SOURCE_DIR}/math/include)
add_subdirectory(math)

add_executable(mathtest main.c)
target_link_libraries(mathtest mymath)
