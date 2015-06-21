set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

find_package( ZLIB REQUIRED )

file(GLOB_RECURSE LIBSWF_SOURCES *.cpp *.h)
add_library(swf ${LIBSWF_SOURCES})
set_target_properties(swf PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR})

if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries( swf ${ZLIB_LIBRARIES} )
endif( ZLIB_FOUND )

add_executable(swfparser main.cpp)
target_link_libraries(swfparser swf)