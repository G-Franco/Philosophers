/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:17:39 by gacorrei          #+#    #+#             */
/*   Updated: 2024/08/24 10:21:46 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Philo
{
    private:
    public:
        Philo();
        Philo(const Philo &copy);
        Philo &operator=(const Philo &copy);
        ~Philo();
};
