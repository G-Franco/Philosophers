/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/09 11:16:08 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	message(t_philo *philo, int n, char *msg, int end)
{
	sem_wait(philo->data->write_s);
	if (!end && end_check(philo->data))
	{
		sem_post(philo->data->write_s);
		return ;
	}
	printf("%lu %i %s\n", get_time() - philo->data->start_time, n + 1, msg);
	sem_post(philo->data->write_s);
	return ;
}

int	end_check(t_data *data)
{
	sem_wait(data->end_s);
	if (data->end)
	{
		sem_post(data->end_s);
		return (1);
	}
	sem_post(data->end_s);
	return (0);
}

void	end(t_data *data)
{
	sem_wait(data->end_s);
	data->end = 1;
	sem_post(data->end_s);
	return ;
}

int	dead(t_philo *philo)
{
	sem_wait(philo->data->last_s);
	if (get_time() - philo->last_meal
		>= philo->data->ttdie)
	{
		end(philo->data);
		message(philo, philo->spot, "died", 1);
		sem_post(philo->data->last_s);
		return (1);
	}
	sem_post(philo->data->last_s);
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
		sem_wait(data->counter_s);
		if (data->philo[i]->meals < data->opt_eat)
			philos_full = 0;
		sem_post(data->counter_s);
	}
	if (data->opt_eat && philos_full == 1)
	{
		end(data);
		return (1);
	}
	return (0);
}
