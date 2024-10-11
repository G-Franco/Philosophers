#pragma once
#include "Philo.hpp"

int check_input(int ac, char **av, data &data);
int philo_atom(int ac, char **av, data &data);
void overseer(std::vector<Philo> &philosophers, data &data);
void philo_life(Philo &philo, data &data);