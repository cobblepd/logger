cmake_minimum_required(VERSION 3.8)

project(logger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

add_executable(logger main.cpp logger.cpp logger.h)

target_link_libraries(logger
    PRIVATE
        spdlog::spdlog
)