/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/04 10:18:45 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->end_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_m);
	return (0);
}

void	end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->end_m);
	return ;
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_m);
	if (get_time() - philo->data->start_time - philo->last_meal
		>= philo->data->ttdie)
	{
		end(philo);
		message(philo, philo->spot, "died", 1);
		pthread_mutex_unlock(&philo->last_meal_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_m);
	return (0);
}

void	shleep(t_philo *philo, time_t time)
{
	time_t	wait;

	wait = get_time() + time;
	while (get_time() < wait)
	{
		if (end_check(philo))
			return ;
		usleep(5000);
	}
	return ;
}
