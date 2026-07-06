cmake_minimum_required(VERSION 3.8)

project(logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

set(PROJECT_HEADERS src/logger.h)
set(PROJECT_SOURCES src/logger.cpp)  

add_library(Logger_lib STATIC
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

target_include_directories(Logger_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Logger_lib
    PUBLIC
        spdlog::spdlog
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Logger_lib
)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()