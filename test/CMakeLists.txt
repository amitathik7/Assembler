include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(order_book_tests order_book_test.cpp)
target_link_libraries(order_book_tests PUBLIC assembler_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(order_book_tests)
