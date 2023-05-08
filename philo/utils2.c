/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/08 16:46:11 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, int n, char *msg, int end)
{
	pthread_mutex_lock(&philo->data->write_m);
	if (!end && end_check(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write_m);
		return ;
	}
	printf("%lu %i %s\n", get_time() - philo->data->start_time, n + 1, msg);
	pthread_mutex_unlock(&philo->data->write_m);
	return ;
}

int	end_check(t_data *data)
{
	pthread_mutex_lock(&data->end_m);
	if (data->end)
	{
		pthread_mutex_unlock(&data->end_m);
		return (1);
	}
	pthread_mutex_unlock(&data->end_m);
	return (0);
}

void	end(t_data *data)
{
	pthread_mutex_lock(&data->end_m);
	data->end = 1;
	pthread_mutex_unlock(&data->end_m);
	return ;
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_m);
	if (get_time() - philo->last_meal
		>= philo->data->ttdie)
	{
		end(philo->data);
		message(philo, philo->spot, "died", 1);
		pthread_mutex_unlock(&philo->last_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_m);
	return (0);
}

int	checker(t_data *data)
{
	int		philos_full;
	int		i;

	i = -1;
	philos_full = 1;
	while (++i < data->n)
	{
		if (dead(data->philo[i]))
			return (1);
		if (!data->opt_eat)
			continue ;
		pthread_mutex_lock(&data->philo[i]->counter_m);
		if (data->philo[i]->meals < data->opt_eat)
			philos_full = 0;
		pthread_mutex_unlock(&data->philo[i]->counter_m);
	}
	if (data->opt_eat && philos_full == 1)
	{
		end(data);
		return (1);
	}
	return (0);
}
