file(GLOB SOURCES "src/*.cpp")

add_executable(testCommon ${SOURCES})

target_link_libraries(testCommon cppCommon)