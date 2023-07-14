project(server)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.74 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    server.hpp
    server.cpp
)

add_executable(server ${SOURCES})

set_target_properties(server PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})