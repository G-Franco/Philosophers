/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:02:17 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/26 12:03:32 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO - Use c++11 and Mutexes
// TODO - Explore usage of c++14 features to improve

// Mutexes (mutual exclusions) are synchronization primitives used to protect
// shared resources from concurrent access, ensuring that only one thread can
// access the resource at a time

#include "Philo.hpp"
#include <string>
#include <thread>

#define START_TIME_LAG 10

void philo_life(int index, data &data) {
  Philo philo(index, data);
  std::this_thread::sleep_until(data.start);
  while (true) {
    // lock_guard automatically unlocks mutex when going out of scope
    {
      std::lock_guard<std::mutex> lock(data.end_m);
      if (data.end)
        break;
    }
    philo.think();
    philo.eat();
    philo.sleep();
  }
}

// Message to be displayed whenever an error occurs in input checks
const std::string USAGE_MESSAGE =
    "Usage: ./philo\n"
    "number_of_philosophers\n"
    "time_to_die time_to_eat\n"
    "time_to_sleep\n"
    "[number_of_times_each_philosopher_must_eat]\n"
    "USE ONLY POSITIVE INTEGERS\n"
    "TIMES MUST BE IN ms";

void check_input(int ac, char **av, int &philos, int &time_to_die,
                 int &time_to_eat, int &time_to_sleep, int &meals) {
  if (ac < 5 || ac > 6)
    throw std::runtime_error(USAGE_MESSAGE);
  // Check if the values are non-positive or overflow
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

main(int ac, char **av) {
  int philos, time_to_die, time_to_eat, time_to_sleep, meals;
  try {
    check_input(ac, av, philos, time_to_die, time_to_eat, time_to_sleep, meals);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  data data(philos, time_to_die, time_to_eat, time_to_sleep, meals);
  std::vector<std::thread> threads;
  // The number of threads is defined by the number of philosophers
  threads.reserve(philos);
  // Add some lag to the start time based on the number of philosophers
  // so that all start the simulation at the same time.
  // Without this, for a large amount of philosophers,
  // some of the later ones may start dead if they are created time_to_die
  // after the start of the simulation
  data.start = std::chrono::steady_clock::now() +
               std::chrono::milliseconds(philos * START_TIME_LAG);
  for (int i = 0; i < philos; i++)
    threads.emplace_back(philo_life, i, std::ref(data));
  for (auto &thread : threads)
    thread.join();
  return 0;
}
