find_package(GTest CONFIG REQUIRED)

message(STATUS "Creating Logger_tests target")

add_executable(Logger_tests
    logger_tests.cpp
)

if(NOT TARGET Logger_tests)
    message(FATAL_ERROR "Tests was not created")
endif()

target_link_libraries(Logger_tests
    PRIVATE
        Logger_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET Logger_tests)