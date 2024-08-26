/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:18:35 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/26 15:48:24 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Philo.hpp"

#define MIN_THINK_THRESHOLD 100
#define THINK_FACTOR 2

Philo::Philo(int id, struct data &data)
    : _id(id + 1), _data(data), _last_meal(data.start), _total_meals(0) {
  _left_fork = (_id % 2) ? _id - 1 : _id % _data.philos;
  _right_fork = (_id % 2) ? _id % _data.philos : _id - 1;
}

Philo::~Philo() {}

// Calculates time until the philosopher dies,
// if there is at least MIN_THINK_THRESHOLD time the philosopher may think,
// otherwise he will eat immediately
void Philo::think() {
  std::chrono::milliseconds think;
  {
    std::lock_guard<std::mutex> lock(_last_m);
    think = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - _last_meal);
  }
  if (think < std::chrono::milliseconds(MIN_THINK_THRESHOLD))
    return;
  std::this_thread::sleep_for(think / THINK_FACTOR);
}

void Philo::eat() {
  {
    std::lock_guard<std::mutex> lock(_data.forks[_left_fork]);
    std::lock_guard<std::mutex> lock(_data.forks[_right_fork]);
    {
      std::lock_guard<std::mutex> lock(_last_m);
      _last_meal = std::chrono::steady_clock::now();
    }
    std::this_thread::sleep_for(_data.time_to_eat);
  }
  if (end_check)
    return;
  {
    std::lock_guard<std::mutex> lock(_meals_m);
    _total_meals++;
  }
}

void Philo::sleep() {
  if (end_check())
    return;
  std::this_thread::sleep_for(std::chrono::microseconds(_data.time_to_sleep));
}

bool Philo::end_check() {
  std::lock_guard<std::mutex> lock(_data.end_m);
  return _data.end;
}

void Philo::message(std::string message) {
  std::lock_guard<std::mutex> lock(_data.write_m);
  auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _data.start).count();
  std::cout << timestamp << " " << _id << " " << message << "\n";
}
