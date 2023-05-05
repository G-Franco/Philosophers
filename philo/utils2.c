/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/05 14:10:21 by gacorrei         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->last_m);
	if (get_time() - philo->data->start_time - philo->last_meal
		>= philo->data->ttdie)
	{
		end(philo);
		message(philo, philo->spot, "died", 1);
		pthread_mutex_unlock(&philo->last_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_m);
	return (0);
}

int	meal_checker(t_philo *philo)
{
	if (!philo->data->opt_eat)
		return (0);
	pthread_mutex_lock(&philo->counter_m);
	if (philo->meals == philo->data->opt_eat)
		philo->data->philos_full++;
	pthread_mutex_unlock(&philo->counter_m);
	if (philo->data->philos_full == philo->data->n)
	{
		end(philo);
		return (1);
	}
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
		//REMOVE?? usleep(100);
	}
	return ;
}
