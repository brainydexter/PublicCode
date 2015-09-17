cmake_minimum_required(VERSION 3.2.2)
project(cpp_dataStructures)
set(CMAKE_BUILD_TYPE Release)

#For the shared library:
set ( PROJECT_LINK_LIBS libcppCommon.dylib )
link_directories( ../common/build )

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories(../common/include/)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(cppDS SHARED ${SOURCES})