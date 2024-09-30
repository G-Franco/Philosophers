cmake_minimum_required(VERSION 3.16)
project(Philo_mutex)

# Add source files
add_executable(philo src/main.cpp src/Philo.cpp src/philo_helper.cpp)

# Define separate executables for each test file
add_executable(philo_tests tests/unit_tests.cpp src/Philo.cpp src/philo_helper.cpp)
target_link_libraries(philo_tests gtest gtest_main)

add_executable(check_input_tests tests/check_input_tests.cpp src/Philo.cpp src/philo_helper.cpp)
target_link_libraries(check_input_tests gtest gtest_main)

add_executable(philo_mut tests/philo_mut_test.cpp src/Philo.cpp src/philo_helper.cpp)
target_link_libraries(philo_mut gtest gtest_main)