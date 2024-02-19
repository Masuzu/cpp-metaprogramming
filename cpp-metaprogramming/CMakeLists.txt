# CMakeList.txt : CMake project for Astatheia, include source and define
# project specific logic here.
#

project ("CPP_METAPROGRAMMING")

set(CPP_METAPROGRAMMING_HEADERS
    "class_introspection.hpp"
)

# Add source to this project's executable.
add_library (cpp_metaprogramming INTERFACE)
target_include_directories(cpp_metaprogramming INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
