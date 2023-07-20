project(server)

# set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable((${PROJECT_NAME}) main.cpp)

# find_package(Boost 1.74 COMPONENTS program_options REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})

target_link_directories(${PROJECT_NAME}
    PUBLIC
    networking
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    networking
    )
