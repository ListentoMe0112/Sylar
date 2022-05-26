cmake_minimum_required(VERSION 3.0)
project(sylar)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++17")

include_directories(
    ${PROJECT_SOURCE_DIR}/sylar,
    "D:\\Programming\\sylar\\3rd\\yaml-cpp\\include",
    "D:\\Programming\\sylar\\3rd\\boost_1_77_0",
)

link_directories(${PROJECT_SOURCE_DIR}/3rd/lib)

set(LIB_SRC
    tests/test.cpp
    sylar/log.cpp
    sylar/utils.cpp
    sylar/config.cpp
)

# add_library(sylar SHARED ${LIB_SRC})

add_executable(test ${LIB_SRC})

find_library(YAML yaml-cpp ${PROJECT_SOURCE_DIR}/3rd/lib)
target_link_libraries(test ${YAML})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
