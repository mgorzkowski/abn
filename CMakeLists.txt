cmake_minimum_required(VERSION 3.15)

set(PROJ "abn")

project(${PROJ})

include_directories(
    include
    include/extra
)

set(SOURCES
    src/abn.c
    src/operations/additive.c
    src/operations/bit.c
    src/operations/multiplicative.c
    src/operations/shift.c
    src/utilities/string.c

    # this is extra code - you can remove it here
    # for more information look at src/extra/README.md
    src/extra/fileoperations.c
)

add_library(${PROJ}-static STATIC
    ${SOURCES}
)

add_library(${PROJ}-shared SHARED
    ${SOURCES}
)
