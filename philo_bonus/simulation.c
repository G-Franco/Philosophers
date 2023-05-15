/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/15 10:27:41 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*status(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	sync_start(philo->data);
	while (1)
	{
		sem_wait(philo->data->last_s);
		if (get_time() - philo->last_meal
			>= philo->data->ttdie)
		{
			message(philo, philo->spot, "died");
			exit(1);
		}
		sem_post(philo->data->last_s);
		usleep(1000);
	}
	return (0);
}

void	think(t_philo *philo)
{
	time_t	time_to_think;

	sem_wait(philo->data->last_s);
	time_to_think = (philo->data->ttdie
			- (get_time() - philo->last_meal)
			- philo->data->tteat) / 2;
	sem_post(philo->data->last_s);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	message(philo, philo->spot, "is thinking");
	usleep(time_to_think * 1000);
}

void	life(t_philo *philo)
{
	sem_wait(philo->data->forks);
	message(philo, philo->spot, "has taken a fork");
	sem_wait(philo->data->forks);
	message(philo, philo->spot, "has taken a fork");
	sem_wait(philo->data->last_s);
	philo->last_meal = get_time();
	sem_post(philo->data->last_s);
	message(philo, philo->spot, "is eating");
	usleep(philo->data->tteat * 1000);
	philo->meals++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->meals == philo->data->opt_eat)
		exit(0);
	message(philo, philo->spot, "is sleeping");
	usleep(philo->data->ttsleep * 1000);
}

void	simulation(t_philo *philo)
{
	if (pthread_create(&philo->id, 0, status, philo))
		exit(1);
	if (pthread_detach(philo->id))
		exit(1);
	sync_start(philo->data);
	if (philo->spot % 2)
		think(philo);
	while (1)
	{
		life(philo);
		think(philo);
	}
}
