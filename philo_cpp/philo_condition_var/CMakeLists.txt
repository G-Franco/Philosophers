cmake_minimum_required(VERSION 3.16)
project(Philo_condition_var)

# Add source files
add_executable(philo src/main.cpp)

# Link Google Test
add_executable(philo_tests tests/unit_tests.cpp)
target_link_libraries(philo_tests gtest gtest_main)