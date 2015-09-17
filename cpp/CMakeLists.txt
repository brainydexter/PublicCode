cmake_minimum_required(VERSION 3.2.2)
project(cpp)

#For the shared library:
set ( PROJECT_LINK_LIBS libcppDS.dylib libcppCommon.dylib)
link_directories( dataStructures/build )
link_directories( common/build )

#Bring the headers, into the project
include_directories(common/include)
include_directories(dataStructures/include)

#Can manually add the sources using the set command as follows:
set(MAINEXEC main.cpp)

add_executable(testDS ${MAINEXEC})
target_link_libraries(testDS ${PROJECT_LINK_LIBS} )