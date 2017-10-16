
# include_directories

    include_directories("the_include_dir")

# aux_source_directory

    aux_source_directory("the_abc_src_dir" ABC_SRC_FILES)

# set

    set(VAR_NAME VAR_VALUE)

# add_library

    add_library(${LIB_NAME} STATIC ${ABC_SRC_FILES} ${DEF_SRC_FILEES})
    add_library(${LIB_NAME} SHARED ${ABC_SRC_FILES} ${DEF_SRC_FILEES})

# add_executable

    add_executable(${EXE_NAME} ${ABC_SRC_FILES})

# target_link_libraries

    target_link_libraries(${EXE_NAME} ${LIB_NAME})
