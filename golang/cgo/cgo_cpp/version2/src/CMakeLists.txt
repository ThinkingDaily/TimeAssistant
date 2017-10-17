cmake_minimum_required(VERSION 3.0)

project(cpp_cgo)

include_directories(${PROJECT_SOURCE_DIR}/file_api/include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

add_subdirectory(file_api)
add_subdirectory(utils)

# main
set (MAIN_SRC main.c)

add_executable(test ${MAIN_SRC})

# libraries
target_link_libraries(test utils)
target_link_libraries(test file_api)
