/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/09 11:59:12 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Starts loop to check simulation end conditions*/
int	status(t_data *data)
{
	t_data	*data_n;

	data_n = (t_data *)data;
	while (get_time() < data_n->start_time)
		continue ;
	while (1)
	{
		if (checker(data))
			return (0);
		usleep(500);
	}
	return (0);
}

/*To avoid philosophers eating straight away after waking up
and monopolizing forks, a delay is necessary to make sure
they start eating at the right time if they can afford it*/
void	think(t_philo *philo)
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
	usleep(time_to_think * 1000);
}

/*All remaining processes except thinking. Philos take forks, eat and sleep
while writing status messages and updating their meal count*/
void	life(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 0);
	pthread_mutex_lock(fork2);
	message(philo, philo->spot, "has taken a fork", 0);
	pthread_mutex_lock(&philo->last_m);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_m);
	message(philo, philo->spot, "is eating", 0);
	usleep(philo->data->tteat * 1000);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	if (!end_check(philo->data))
	{
		pthread_mutex_lock(&philo->counter_m);
		philo->meals++;
		pthread_mutex_unlock(&philo->counter_m);
	}
	message(philo, philo->spot, "is sleeping", 0);
	usleep(philo->data->ttsleep * 1000);
	return ;
}

/*If the simulation only has 1 philo he will die after ttdie*/
void	*single(t_philo *philo, pthread_mutex_t *fork1)
{
	pthread_mutex_lock(fork1);
	message(philo, philo->spot, "has taken a fork", 0);
	usleep(philo->data->ttdie * 1000);
	message(philo, philo->spot, "died", 0);
	pthread_mutex_unlock(fork1);
	return (0);
}

/*Delays start so that everyone is synchronized.
Ensures that even and odd philos start at different
points in logic to avoid everyone going for the forks
at the same time.
Main loop repeats while checking for the end of simulation flag*/
void	*simulation(void *philos)
{
	t_philo			*philo;

	philo = (t_philo *)philos;
	while (get_time() < philo->data->start_time)
		usleep(1000);
	if (philo->data->n == 1)
		return (single(philo, philo->fork1));
	if (philo->spot % 2)
		think(philo);
	while (!end_check(philo->data))
	{
		life(philo, philo->fork1, philo->fork2);
		think(philo);
	}
	return (0);
}
