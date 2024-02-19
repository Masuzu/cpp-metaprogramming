project ("TEST")

# Add source to this project's executable.
add_executable (test "main.cpp")

target_link_libraries(test PRIVATE cpp_metaprogramming)
