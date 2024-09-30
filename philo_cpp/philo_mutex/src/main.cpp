// TODO - Use c++11 and Mutexes
// TODO - Explore usage of c++14 features to improve

// Mutexes (mutual exclusions) are synchronization primitives used to protect
// shared resources from concurrent access, ensuring that only one thread can
// access the resource at a time

#include "../include/Philo.hpp"
#include "../include/philo_helper.hpp"

int main(int ac, char **av, data &data) {
  return philo_mut(ac, av, data);
}
