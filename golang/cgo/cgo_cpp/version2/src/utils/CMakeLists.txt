include_directories(include)

aux_source_directory("src" UTILS_SRC_FILES)

add_library(utils ${UTILS_SRC_FILES})
