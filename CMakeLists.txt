cmake_minimum_required(VERSION 3.27.1)

# Set the project name
project(WeightGainCalculator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost
find_package(Boost REQUIRED)

# Add the executable
add_executable(WeightGainCalculator src/main.cpp)  # replace 'main.cpp' with the name of your source file

# Link Boost libraries
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(WeightGainCalculator ${Boost_LIBRARIES})
endif()
