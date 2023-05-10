/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/10 14:25:53 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	status(t_data *data)
{
	sync_start(data);
	while (1)
	{
		if (checker(data))
			return (0);
		usleep(1000);
	}
	return (0);
}

void	think(t_philo *philo)
{
	time_t	time_to_think;

	sem_wait(philo->last_s);
	time_to_think = (philo->data->ttdie
			- (get_time() - philo->last_meal)
			- philo->data->tteat) / 2;
	sem_post(philo->last_s);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	message(philo, philo->spot, "is thinking", 0);
	usleep(time_to_think * 1000);
}

void	life(t_philo *philo)
{
	sem_wait(philo->data->forks);
	message(philo, philo->spot, "has taken a fork", 0);
	sem_wait(philo->data->forks);
	message(philo, philo->spot, "has taken a fork", 0);
	sem_wait(philo->last_s);
	philo->last_meal = get_time();
	sem_post(philo->last_s);
	message(philo, philo->spot, "is eating", 0);
	usleep(philo->data->tteat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (!end_check(philo->data))
	{
		sem_wait(philo->counter_s);
		philo->meals++;
		sem_post(philo->counter_s);
	}
	message(philo, philo->spot, "is sleeping", 0);
	usleep(philo->data->ttsleep * 1000);
	return ;
}

void	*single(t_philo *philo)
{
	sem_wait(philo->data->forks);
	message(philo, philo->spot, "has taken a fork", 0);
	usleep(philo->data->ttdie * 1000);
	message(philo, philo->spot, "died", 0);
	sem_post(philo->data->forks);
	return (0);
}

int	reopen(t_philo *philo)
{
	philo->data->forks = sem_open("/forks_s", O_CREAT, 0644, philo->data->n);
	philo->data->write_s = sem_open("/write_s", O_CREAT, 0644, 1);
	philo->data->end_s = sem_open("/end_s", O_CREAT, 0644, 1);
	philo->counter_s = sem_open("/counter_s", O_CREAT, 0644, 1);
	philo->last_s = sem_open("/last_s", O_CREAT, 0644, 1);
	if (philo->data->forks == SEM_FAILED || philo->data->write_s == SEM_FAILED
		|| philo->data->end_s == SEM_FAILED || philo->counter_s == SEM_FAILED
		|| philo->last_s == SEM_FAILED)
		return (1);
	return (0);
}

void	*simulation(t_philo *philo)
{
	if (reopen(philo))
		return (0);
	sync_start(philo->data);
	if (philo->data->n == 1)
		return (single(philo));
	if (philo->spot % 2)
		think(philo);
	while (!end_check(philo->data))
	{
		life(philo);
		think(philo);
	}
	return (0);
}
