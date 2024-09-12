cmake_minimum_required(VERSION 3.27.1)

# Set the project name
project(AsioLearn)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find Boost
find_package(Boost REQUIRED)

# Add the executable
add_executable(AsioLearn src/main.cpp)
add_executable(server_l3 src/lesson3/server.cpp)
add_executable(client_l3 src/lesson3/client.cpp)

# Link Boost libraries
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(AsioLearn ${Boost_LIBRARIES})
    target_link_libraries(server_l3 ${Boost_LIBRARIES})
    target_link_libraries(client_l3 ${Boost_LIBRARIES})
endif()