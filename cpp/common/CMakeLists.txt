cmake_minimum_required(VERSION 3.2.2)
project(cpp_common)

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

# Generate the shared library from the sources
add_library(cppCommon SHARED ${SOURCES})

# Specify that this library itself needs access to the folder "common/include" and that any other
# target which depends on this also gets similar access - i.e. use 'PUBLIC'
target_include_directories(cppCommon PUBLIC include)
