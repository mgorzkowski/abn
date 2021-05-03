cmake_minimum_required(VERSION 3.15)

set(PROJ "abn_sample")
project(${PROJ})

set(SOURCES
    sample.c
)

add_subdirectory(3rd_party/abn)
include_directories(3rd_party/abn/include)

add_executable(${PROJ} ${SOURCES})

target_link_libraries(${PROJ}
    abn-static
)
