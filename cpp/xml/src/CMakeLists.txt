cmake_minimum_required(VERSION 3.4)

project(xml_test)

find_library(LIB_XML2 xml2 REQUIRED)

include_directories(/usr/include/libxml2)

aux_source_directory("." SRC_FILES)
add_executable(xml_test ${SRC_FILES})

message("LIB_XML2: ${LIB_XML2}")
target_link_libraries(xml_test ${LIB_XML2})
