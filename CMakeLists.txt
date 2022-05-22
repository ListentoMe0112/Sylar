cmake_minimum_required(VERSION 3.0)
project(sylar)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -g -std=c++11 -Wall -Wno-deprecated -Wno-unused-funcion")

set(LIB_SRC
    sylar/log.cpp
)

add_library(sylar SHARED ${LIB_SRC})
# add_library(sylar STATIC ${LIB_SRC})
include_directories(
    ${PROJECT_SOURCE_DIR}/sylar
)
add_executable(test tests/test.cpp)
add_dependencies(test sylar)
target_link_libraries(test sylar)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
