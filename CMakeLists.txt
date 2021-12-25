cmake_minimum_required(VERSION 3.5)

project(Server)

# Main definitions
set(CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
)

set(TEST_INCLUDES
    ${CORE_INCLUDES}
    test/framework
)

set(TEST_CFLAGS
    -g -O0 --std=c++14 -Wno-writable-strings
)

## Server library
add_library(core STATIC 
    src/application/game_server.c
    src/infrastructure/list.c
    src/infrastructure/log.c
    src/infrastructure/server.c
)

target_include_directories(core PUBLIC ${CORE_INCLUDES})

## Server binary
add_executable(server src/main.c)
target_link_libraries(server PRIVATE core)

## Tests
add_executable(test_list
    test/test_list.cpp
)

target_compile_options(test_list PRIVATE ${TEST_CFLAGS})
target_include_directories(test_list PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_list PRIVATE core)
