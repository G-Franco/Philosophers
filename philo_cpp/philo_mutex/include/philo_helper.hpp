#pragma once
#include "../include/struct.hpp"
#include "../include/Philo.hpp"
#include <iostream>
#include <string>

void check_input(int ac, char **av, int &philos, int &time_to_die,
                 int &time_to_eat, int &time_to_sleep, int &meals);
void philo_life(Philo &philo, data &data);
void end(data &data);
void overseer(std::vector<Philo> &philosophers, data &data);
int philo_mut(int ac, char **av, data &data);
