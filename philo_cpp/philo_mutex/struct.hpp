/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:02:08 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/26 11:11:18 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <chrono>
#include <mutex>
#include <vector>

struct data {
  int philos;
  std::chrono::milliseconds time_to_die;
  std::chrono::milliseconds time_to_eat;
  std::chrono::milliseconds time_to_sleep;
  std::chrono::time_point<std::chrono::steady_clock> start;
  int meals;
  bool end;
  std::vector<std::mutex> forks;
  std::mutex end_m;
  std::mutex write_m;

  data(int philos, int die, int eat, int sleep, int meals)
      : philos(philos),
        time_to_die(std::chrono::milliseconds(die)),
        time_to_eat(std::chrono::milliseconds(eat)),
        time_to_sleep(std::chrono::milliseconds(sleep)),
        meals(meals), forks(philos), end(false) {}
};
