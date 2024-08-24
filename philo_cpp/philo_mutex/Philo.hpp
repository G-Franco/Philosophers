/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:17:39 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/24 15:26:48 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "struct.hpp"

class Philo
{
    private:
      int   _id;
      data  *_data;
      int   _left_fork;
      int   _right_fork;
      int   _last_meal;
      int   _total_meals;

    public:
      Philo(int id, struct data &data);
      ~Philo();
};
