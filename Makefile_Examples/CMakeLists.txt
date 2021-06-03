# this should be on same level as you have a src folder and a includes folder

cmake_minimum_required(VERSION 3.0)

SET(PROJECT "CppThreads")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 11)

file(GLOB PR_HEADER_FILES "includes/*.h")
file(GLOB PR_SOURCE_FILES "src/*.cpp")

set(SOURCE_FILES
	${PR_HEADER_FILES}
	${PR_SOURCE_FILES}
	)

source_group("Header Files" FILES ${PR_HEADER_FILES})
source_group("Source Files" FILES ${PR_SOURCE_FILES})

file(GLOB LOCAL_INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_CURRENT_LIST_DIR}/includes")
include_directories(${LOCAL_INCLUDE_PATHS})

add_executable( ${PROJECT} ${SOURCE_FILES} )


######################################################
cmake_minimum_required(VERSION 3.0)

SET(PROJECT "projectAuction")
project( ${PROJECT} )

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION "$VERSION_MAJOR $VERSION_MINOR")

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES "src/*.cpp" "src/*.h")

add_executable( ${PROJECT} ${SOURCES} )