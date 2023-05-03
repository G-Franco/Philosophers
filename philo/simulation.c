/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/02 13:24:32 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*status(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (get_time() < philo->data->start_time)
		continue ;
	while (1)
	{
		pthread_mutex_lock(&philo->last_meal_m);
		if (get_time() - philo->data->start_time - philo->last_meal >= philo->data->ttdie)
		{
			end(philo);
			message(philo, philo->spot, "died", 1);
			pthread_mutex_unlock(&philo->last_meal_m);
			return (0);
		}
		pthread_mutex_unlock(&philo->last_meal_m);
		pthread_mutex_lock(&philo->data->meals);
		pthread_mutex_lock(&philo->meals_m);
		if (philo->meals == philo->data->opt_eat)
			philo->data->philos_full++;
		pthread_mutex_unlock(&philo->meals_m);
		if (philo->data->philos_full == philo->data->opt_eat)
		{
			end(philo);
			pthread_mutex_unlock(&philo->data->meals);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->meals);
	}
	return (0);
}

void	life(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	message(philo, philo->spot, "is thinking", 1);
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 1);
	pthread_mutex_lock(fork2);
	message(philo, philo->spot, "has taken a fork", 1);
	if (!end_check(philo))
		message(philo, philo->spot, "is eating", 1);
	else
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return ;
	}
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	usleep(philo->data->tteat * 1000);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	pthread_mutex_lock(&philo->meals_m);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_m);
	message(philo, philo->spot, "is sleeping", 1);
	usleep(philo->data->ttsleep * 1000);
	return ;
}

void	*single(t_philo *philo, pthread_mutex_t *fork1)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 1);
	usleep(philo->data->ttdie * 1000);
	message(philo, philo->spot, "died", 1);
	pthread_mutex_unlock(fork1);
	return (0);
}

void	*simulation(void *philos)
{
	t_philo			*philo;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	philo = (t_philo *)philos;
	fork1 = philo->data->forks[philo->spot - 1];
	if (philo->spot == 1)
		fork2 = philo->data->forks[philo->data->n - 1];
	else
		fork2 = philo->data->forks[philo->spot - 2];
	while (get_time() < philo->data->start_time)
		continue ;
	if (philo->data->n == 1)
		return (single(philo, fork1));
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	if (!(philo->spot % 2))
		usleep(10000);
	while (!end_check(philo))
		life(philo, fork1, fork2);
	return (0);
}
