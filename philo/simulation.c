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
	while (get_time() - philo->data->start_time - philo->last_meal < philo->data->ttdie)
	{
		if (philo->meals == philo->data->opt_eat)
		{
			pthread_mutex_lock(&philo->data->meals);
			philo->data->philos_full++;
			pthread_mutex_unlock(&philo->data->meals);
		}
		if (philo->data->philos_full == philo->data->opt_eat)
		{
			/*FINISHED EATING MESSAGE?*/
		}
	}
	pthread_mutex_lock(&philo->data->end_m);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->end_m);
	message(philo, philo->spot, "died", 0);
	pthread_mutex_lock(&philo->data->write);
	/*Lock forks and exit?*/
	return (0);
}

void	eat(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 1);
	pthread_mutex_lock(fork2);
	message(philo, philo->spot, "has taken a fork", 1);
	message(philo, philo->spot, "is eating", 1);
	pthread_mutex_lock(&philo->data->meals);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meals);
	usleep(philo->data->tteat * 1000);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	philo->meals++;
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
	if (philo->data->n == 1)
		return (single(philo, fork1));
	if (philo->spot == 1)
		fork2 = philo->data->forks[philo->data->n - 1];
	else
		fork2 = philo->data->forks[philo->spot - 2];
	while (get_time() < philo->data->start_time)
		continue ;
	pthread_mutex_lock(&philo->data->meals);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meals);
	if (philo->id % 2)
		usleep(philo->data->ttsleep * 1000);
	/*Should philos keep eating after reaching max meals?*/
	while (!end(philo))
	{
		message(philo, philo->spot, "is thinking", 1);
		eat(philo, fork1, fork2);
		message(philo, philo->spot, "is sleeping", 1);
		usleep(philo->data->ttsleep * 1000);
	}
	return (0);
}
