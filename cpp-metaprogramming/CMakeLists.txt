project ("CPP_METAPROGRAMMING")

add_library (cpp_metaprogramming INTERFACE)
target_include_directories(cpp_metaprogramming INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
