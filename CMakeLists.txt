cmake_minimum_required(VERSION 3.15)
project(client)

add_subdirectory(client)
add_subdirectory(networking)

option(BUILD_SERVER "Whether or not build examples" ON)

if(BUILD_SERVER)
    message(STATUS "Building server...")
    add_subdirectory(server)
endif()