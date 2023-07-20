project(networking)

find_package(Boost 1.74 COMPONENTS program_options REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCES src/* src/*/* src/*/*/*)

add_library(networking tcp_connection.cpp tcp_server.cpp)

target_include_directories(networking 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)



set_target_properties(networking PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(networking ${Boost_LIBRARIES})