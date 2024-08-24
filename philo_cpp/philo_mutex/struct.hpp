/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:02:08 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/24 15:15:10 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <mutex>
#include <vector>

struct data {
  int philos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int meals;
  bool end;
  std::vector<std::mutex> forks;
  std::mutex end_m;
  std::mutex write_m;

  data(int philos, int die, int eat, int sleep, int meals)
      : philos(philos), time_to_die(die), time_to_eat(eat),
        time_to_sleep(sleep), meals(meals), forks(philos), end(false) {}
};
