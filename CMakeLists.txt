cmake_minimum_required(VERSION 3.29)
project(uuid)

set(CMAKE_C_STANDARD 23)

add_library(uuid STATIC uuid.c)

if(WIN32)
    target_link_libraries(uuid PRIVATE Rpcrt4)
endif()
