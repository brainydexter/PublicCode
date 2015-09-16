cmake_minimum_required(VERSION 2.8.9)
project(dataStructures)

#Bring the headers, into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
set(MAINEXEC main.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(testDS ${SOURCES} ${MAINEXEC})