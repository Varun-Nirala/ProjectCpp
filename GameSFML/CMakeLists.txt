cmake_minimum_required(VERSION 3.0)

SET(PROJECT "GameSFML")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES "src/*.cpp" "src/*.h")

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "D:/Varun/Varun_Work/Libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable( ${PROJECT} ${SOURCES} )
target_link_libraries(${PROJECT} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)