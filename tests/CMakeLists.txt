project ("TESTS")

add_executable (tests "main.cpp" "class_instrospection_tests.cpp" "loop_unrolling_tests.cpp" "parameter_pack_utils_tests.cpp")

target_link_libraries(tests PRIVATE cpp_metaprogramming GTest::gtest_main)
target_link_options(tests PRIVATE -static-libgcc -static-libstdc++)

include(GoogleTest)
gtest_discover_tests(tests)