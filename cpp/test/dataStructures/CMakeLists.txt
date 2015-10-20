# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

# Generate the shared library from the sources
add_library(testCppDS SHARED ${SOURCES})

# Specify that this library itself needs access to the folder "dataStructures/include" and that any
# other target which depends on this also gets similar access - i.e. use 'PUBLIC'
target_include_directories(testCppDS PUBLIC include)

# Specify that this library depends upon cppCommon
target_link_libraries(testCppDS cppDS)