// TODO - Use c++11 and atomic variables
// TODO - Explore usage of c++14 features to improve

// Atomic variables allow for lock-free, thread-safe operations on shared data.
// Atomic operations complete without the possibility of interruption,
// ensuring data consistency in concurrent environments.

#include "../include/Philo_helper.hpp"

int main(int ac, char **av)
{
  data data;
  return philo_atom(ac, av, data);
}
