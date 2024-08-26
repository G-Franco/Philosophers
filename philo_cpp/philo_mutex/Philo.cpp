/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:18:35 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/26 12:03:04 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.hpp"

Philo::Philo(int id, struct data &data)
    : _id(id + 1), _data(data), _last_meal(data.start), _total_meals(0) {
  _left_fork = (_id % 2) ? _id - 1 : _id % _data.philos;
  _right_fork = (_id % 2) ? _id % _data.philos : _id - 1;
}

Philo::~Philo() {}
