/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/05 14:46:33 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, int n, char *msg, int end)
{
	pthread_mutex_lock(&philo->data->write_m);
	if (!end && end_check(philo))
	{
		pthread_mutex_unlock(&philo->data->write_m);
		return ;
	}
	printf("%lu %i %s\n", get_time() - philo->data->start_time, n + 1, msg);
	pthread_mutex_unlock(&philo->data->write_m);
	return ;
}

int	status(t_data *data)
{
	t_data	*data_n;
	int		i;

	data_n = (t_data *)data;
	while (get_time() < data_n->start_time)
		continue ;
	while (1)
	{
		data->philos_full = 1;
		i = -1;
		while (++i < data_n->n)
		{
			if (dead(data_n->philo[i]) || meal_checker(data_n->philo[i]))
				return (0);
		}
		usleep(500);
	}
	return (0);
}

/* static void	think_routine(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->data->last_m);
	time_to_think = (philo->data->ttdie
			- (get_time() - philo->last_meal)
			- philo->data->tteat) / 2;
	pthread_mutex_unlock(&philo->data->last_m);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	message(philo, philo->spot, "is thinking", 0);
	shleep(philo, time_to_think);
} */

static void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->last_m);
	time_to_think = (philo->data->ttdie
			- (get_time() - philo->last_meal)
			- philo->data->tteat) / 2;
	pthread_mutex_unlock(&philo->last_m);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	message(philo, philo->spot, "is thinking", 0);
	shleep(time_to_think);
}

void	life(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 0);
	pthread_mutex_lock(fork2);
	message(philo, philo->spot, "has taken a fork", 0);
	message(philo, philo->spot, "is eating", 0);
	pthread_mutex_lock(&philo->last_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_m);
	shleep(philo->data->tteat);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	if (!end_check(philo))
	{
		pthread_mutex_lock(&philo->counter_m);
		philo->meals++;
		pthread_mutex_unlock(&philo->counter_m);
	}
	message(philo, philo->spot, "is sleeping", 0);
	shleep(philo->data->ttsleep);
	return ;
}

void	*single(t_philo *philo, pthread_mutex_t *fork1)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 0);
	usleep(philo->data->ttdie * 1000);
	message(philo, philo->spot, "died", 0);
	pthread_mutex_unlock(fork1);
	return (0);
}

void	*simulation(void *philos)
{
	t_philo			*philo;

	philo = (t_philo *)philos;
	while (get_time() < philo->data->start_time)
		continue ;
	if (philo->data->n == 1)
		return (single(philo, philo->fork1));
	pthread_mutex_lock(&philo->last_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_m);
	if (philo->spot % 2)
		think(philo);
	while (!end_check(philo))
	{
		life(philo, philo->fork1, philo->fork2);
		think(philo);
	}
	return (0);
}
