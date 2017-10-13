project(Hello)

aux_source_directory("." SRC_FILES)
add_executable(hello ${SRC_FILES})
