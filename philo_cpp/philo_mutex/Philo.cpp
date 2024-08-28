/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:18:35 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/28 10:46:33 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.hpp"

#define MIN_THINK_THRESHOLD 100
#define THINK_FACTOR 2

Philo::Philo(int id, struct data &data)
    : _id(id + 1), _data(data), _last_meal(data.start), _total_meals(0) {
  _left_fork = (_id % 2) ? _id - 1 : _id % _data.philos;
  _right_fork = (_id % 2) ? _id % _data.philos : _id - 1;
}

Philo::~Philo() {}

Philo::Philo(Philo &&other) noexcept
    : _id(other._id), _data(other._data), _left_fork(other._left_fork),
      _right_fork(other._right_fork), _last_meal(other._last_meal), _last_m(),
      _meals_m(), _total_meals(other._total_meals) {
  other._left_fork = -1;
  other._right_fork = -1;
  other._total_meals = 0;
}

Philo &Philo::operator=(Philo &&other) noexcept {
  if (this != &other) {
    _id = other._id;
    _left_fork = other._left_fork;
    _right_fork = other._right_fork;
    _last_meal = other._last_meal;
    _total_meals = other._total_meals;
    other._left_fork = -1;
    other._right_fork = -1;
    other._total_meals = 0;
  }
  return *this;
}

// Calculates time until the philosopher dies,
// if there is at least MIN_THINK_THRESHOLD time the philosopher may think,
// otherwise he will eat immediately
void Philo::think() {
  std::chrono::milliseconds think;
  {
    std::lock_guard<std::mutex> last(_last_m);
    think = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - _last_meal);
  }
  message("is thinking", false);
  if (think < std::chrono::milliseconds(MIN_THINK_THRESHOLD))
    return;
  std::this_thread::sleep_for(think / THINK_FACTOR);
}

void Philo::eat() {
  if (_data.philos == 1) {
    std::lock_guard<std::mutex> left(_data.forks[_left_fork]);
    message("has taken a fork", false);
    std::this_thread::sleep_for(_data.time_to_die);
    return;
  }
  {
    std::lock_guard<std::mutex> left(_data.forks[_left_fork]);
    message("has taken a fork", false);
    std::lock_guard<std::mutex> right(_data.forks[_right_fork]);
    message("has taken a fork", false);
    {
      std::lock_guard<std::mutex> last(_last_m);
      _last_meal = std::chrono::steady_clock::now();
    }
    message("is eating", false);
    std::this_thread::sleep_for(_data.time_to_eat);
  }
  if (end_check())
    return;
  {
    std::lock_guard<std::mutex> meals(_meals_m);
    _total_meals++;
  }
}

void Philo::sleep() {
  if (end_check())
    return;
  message("is sleeping", false);
  std::this_thread::sleep_for(_data.time_to_sleep);
}

bool Philo::end_check() {
  std::lock_guard<std::mutex> end(_data.end_m);
  return _data.end;
}

void Philo::dead() { message("died", true); }

// Using char* over std::string here to avoid the (miniscule) performance
// hit of having to allocate memory, constructing and destructing the string
// object. Since this function is called often and locks mutexes it seems
// sensible.
void Philo::message(const char *message, bool final) {
  if (!final && end_check())
    return;
  std::lock_guard<std::mutex> write(_data.write_m);
  auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::steady_clock::now() - _data.start)
                       .count();
  std::cout << timestamp << " " << _id << " " << message << "\n";
}

int Philo::get_total_meals() {
  std::lock_guard<std::mutex> meals(_meals_m);
  return _total_meals;
}

std::chrono::time_point<std::chrono::steady_clock> Philo::get_last_meal() {
  std::lock_guard<std::mutex> last(_last_m);
  return _last_meal;
}
