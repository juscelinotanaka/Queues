cmake_minimum_required(VERSION 3.6)
project(QueueLib)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../Unity/Queues/Assets/Plugins/")

set(SOURCE_FILES library.cpp library.h TimedQueue.cpp TimedQueue.h mt.cpp mt.h ServerList.cpp ServerList.h)
add_library(QueueLib SHARED ${SOURCE_FILES})

set_target_properties(QueueLib
        PROPERTIES PREFIX ""
        SUFFIX ".bundle"
        )