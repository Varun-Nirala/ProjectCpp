cmake_minimum_required(VERSION 3.0)

SET(PROJECT "OpenGL")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/Engine)
include_directories(${CMAKE_SOURCE_DIR}/src/Graphics)

file(GLOB SOURCES "src/*.cpp" "src/*.h" "src/Engine/*.h" "src/Engine/*.cpp" "src/Graphics/*.h" "src/Graphics/*.cpp")

add_executable( ${PROJECT} ${SOURCES} )