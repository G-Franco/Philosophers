/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:17:39 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/27 12:18:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "struct.hpp"
#include <iostream>
#include <thread>

class Philo {
private:
  int _id;
  data &_data;
  int _left_fork;
  int _right_fork;
  std::chrono::time_point<std::chrono::steady_clock> _last_meal;
  std::mutex _last_m;
  std::mutex _meals_m;
  int _total_meals;

public:
  Philo(int id, struct data &data);
  ~Philo();
  Philo(Philo &&other) noexcept;
  Philo &operator=(Philo &&other) noexcept;
  void think();
  void eat();
  void sleep();
  bool end_check();
  void dead();
  void message(const char *message, bool final);
  int get_total_meals();
  std::chrono::time_point<std::chrono::steady_clock> get_last_meal();
};
