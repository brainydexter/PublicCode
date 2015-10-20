cmake_minimum_required(VERSION 3.1.2)
project(cpp)

add_subdirectory(common)
add_subdirectory(dataStructures)
add_subdirectory(test)

add_executable(execCpp main.cpp)

# Specify that this exe depends upon cppDS.  Since cppDS already has a dependency on cppCommon, that
# dependency is also applied to execCpp, so execCpp will cause cppDS and cppCommon to be built before
# it is built.
target_link_libraries(execCpp cppDS testCpp)
