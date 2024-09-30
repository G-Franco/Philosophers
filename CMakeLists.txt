cmake_minimum_required(VERSION 3.16)
project(Philo_cpp)

# Add Google Test
add_subdirectory(googletest)

# Add projects
add_subdirectory(philo_cpp/philo_mutex)
add_subdirectory(philo_cpp/philo_monitor)
add_subdirectory(philo_cpp/philo_condition_var)
add_subdirectory(philo_cpp/philo_atomic_var)
