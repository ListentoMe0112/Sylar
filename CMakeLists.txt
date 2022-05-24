cmake_minimum_required(VERSION 3.0)
project(sylar)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++17")

include_directories(
    ${PROJECT_SOURCE_DIR}/sylar
)

set(LIB_SRC
    tests/test.cpp
    sylar/log.cpp
    sylar/utils.cpp
)


# add_library(sylar SHARED ${LIB_SRC})

add_executable(test ${LIB_SRC})

# add_dependencies(test sylar)
# target_link_libraries(test sylar)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
