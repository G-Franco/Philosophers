cmake_minimum_required(VERSION 3.16)
project(Philo_atomic_var)

# Add source files
add_executable(philo src/main.cpp src/philo_helper.cpp src/Philo.cpp)

# Define separate executables for each test file
add_executable(philo_atom_input tests/src/input_tests.cpp src/philo_helper.cpp src/Philo.cpp)
target_link_libraries(philo_atom_input gtest gtest_main)

add_executable(philo_atom_unit tests/src/unit_tests.cpp src/philo_helper.cpp src/Philo.cpp)
target_link_libraries(philo_atom_unit gtest gtest_main)

add_executable(philo_atom_system tests/src/system_tests.cpp src/philo_helper.cpp src/Philo.cpp)
target_link_libraries(philo_atom_system gtest gtest_main)