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
			message(philo, philo->spot, "died");
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
	message(philo, philo->spot, "is thinking");
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork");
	pthread_mutex_lock(fork2);
	message(philo, philo->spot, "has taken a fork");
	message(philo, philo->spot, "is eating");
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	shleep(philo, philo->data->tteat);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	if (!end_check(philo))
	{
		pthread_mutex_lock(&philo->meals_m);
		philo->meals++;
		pthread_mutex_unlock(&philo->meals_m);
	}
	message(philo, philo->spot, "is sleeping");
	shleep(philo, philo->data->ttsleep);
	return ;
}

void	*single(t_philo *philo, pthread_mutex_t *fork1)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork");
	usleep(philo->data->ttdie);
	message(philo, philo->spot, "died");
	pthread_mutex_unlock(fork1);
	return (0);
}

void	*simulation(void *philos)
{
	t_philo			*philo;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	philo = (t_philo *)philos;
	if (!(philo->spot % 2))
	{
		fork1 = philo->data->forks[philo->spot];
		fork2 = philo->data->forks[(philo->spot + 1) % philo->data->n];
	}
	else
	{
		fork1 = philo->data->forks[(philo->spot + 1) % philo->data->n];
		fork2 = philo->data->forks[philo->spot];
	}
	while (get_time() < philo->data->start_time)
		continue ;
	if (philo->data->n == 1)
		return (single(philo, fork1));
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->last_meal_m);
	if (philo->spot % 2)
		usleep(1000);
	while (!end_check(philo))
		life(philo, fork1, fork2);
	return (0);
}
