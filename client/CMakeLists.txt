project(client)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.74 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
    client.hpp
    client.cpp
)

add_executable(client ${SOURCES})

set_target_properties(client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})