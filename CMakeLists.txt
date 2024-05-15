cmake_minimum_required(VERSION 3.26)
project(Trade C)

set(TARGET_NAME trade)
set(EXECUTABLE_NAME trade)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_FLAGS "-Wall -Wextra")

add_library(build_configs INTERFACE)

target_compile_options(build_configs INTERFACE
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:RELEASE>:-O3>
        -march=native
        -flto=auto
)

target_compile_definitions(build_configs INTERFACE
        $<$<CONFIG:DEBUG>:DEBUG>
        $<$<CONFIG:RELEASE>:NDEBUG>
        BRACKET_O={
        BRACKET_C=}
        "SEMICOLON=\;"
)

target_link_options(build_configs INTERFACE
        -flto=auto
)

add_executable(${TARGET_NAME}
        src/main.c
        src/chart.c
        src/settings_utils.c
        src/input.c
        src/array.c
        src/balance.c
        src/trade.c
        src/loader.c
)

target_include_directories(${TARGET_NAME} PRIVATE
        include
)

target_link_libraries(${TARGET_NAME} PRIVATE
        build_configs
        m
)

set_target_properties(${TARGET_NAME} PROPERTIES
        OUTPUT_NAME ${EXECUTABLE_NAME}
)

add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD COMMAND cp ${EXECUTABLE_NAME} ../
)
