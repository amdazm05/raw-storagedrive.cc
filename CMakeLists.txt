cmake_minimum_required(VERSION 3.0)
project(RW_NFS)
add_library(   
    rwnfs
        STATIC
    ${PROJECT_SOURCE_DIR}/src/win_rwnfs.cpp
)

target_include_directories(
    rwnfs
        PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp )
target_link_libraries(main PUBLIC rwnfs)
