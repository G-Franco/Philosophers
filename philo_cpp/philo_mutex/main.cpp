/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:02:17 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/24 11:45:31 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO - Use c++11 and Mutexes
// TODO - Explore usage of c++14 features to improve

// Mutexes (mutual exclusions) are synchronization primitives used to protect
// shared resources from concurrent access, ensuring that only one thread can
// access the resource at a time

#include "Philo.hpp"
#include <string>

const std::string USAGE_MESSAGE =
    "Usage: ./philo\n"
    "number_of_philosophers\n"
    "time_to_die time_to_eat\n"
    "time_to_sleep\n"
    "[number_of_times_each_philosopher_must_eat]\n"
    "USE ONLY POSITIVE INTEGERS\n"
    "TIMES MUST BE IN ms";

void check_input(int ac, char **av) {
  int philos, time_to_die, time_to_eat, time_to_sleep, meals;

  if (ac < 5 || ac > 6) {
    throw std::runtime_error(USAGE_MESSAGE);
  }

  try {
    philos = std::stoi(av[1]);
    time_to_die = std::stoi(av[2]);
    time_to_eat = std::stoi(av[3]);
    time_to_sleep = std::stoi(av[4]);
    meals = ac == 6 ? std::stoi(av[5]) : 0;
    if (philos <= 0 || time_to_die <= 0 || time_to_eat <= 0 ||
        time_to_sleep <= 0 || (ac == 6 && meals <= 0))
      throw std::runtime_error(USAGE_MESSAGE);
  } catch (const std::exception &e) {
    throw std::runtime_error(USAGE_MESSAGE);
  }
}

int main(int ac, char **av) {
  try {
    check_input(ac, av);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
