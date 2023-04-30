/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/30 11:35:58 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(unsigned long start_time, int n, int flag)
{
	/*FIND BEST WAY TO PROTECT MESSAGE!!!!*/
	if (flag == 0)
		printf("%lu %i has taken a fork\n", get_time() - start_time, n);
	if (flag == 1)
		printf("%lu %i is eating\n", get_time() - start_time, n);
	if (flag == 2)
		printf("%lu %i is sleeping\n", get_time() - start_time, n);
	if (flag == 3)
		printf("%lu %i is thinking\n", get_time() - start_time, n);
	if (flag == 4)
		printf("%lu %i died\n", get_time() - start_time, n);
	return ;
}



void	think(t_philo *philo)
{
	message(philo->data->start_time, philo->spot, 3);
	return ;
}

void	eat(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	message(philo->data->start_time, philo->spot, 1);
	usleep(philo->data->tteat * 1000);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	philo->meals++;
	return ;
}

void	shleep(t_philo *philo)
{
	message(philo->data->start_time, philo->spot, 2);
	usleep(philo->data->ttsleep * 1000);
}

void	*simulation(void *philos)
{
	t_philo			*philo;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	philo = (t_philo *)philos;
	fork1 = philo->data->forks[philo->spot];
	if (philo->spot == 0)
		fork2 = philo->data->forks[philo->data->n - 1];
	else
		fork2 = philo->data->forks[philo->spot - 1];
	philo->last_meal = get_time();
	/*CHECK IF THIS IS ALLOWED!!!*/
	if (philo->spot % 2)
		usleep(philo->data->ttsleep * 1000);
	/*SHOULD THE PHILO KEEP IN LOOP UNTIL ALL OTHERS HAVE EATEN THE REQUIRED AMOUNT OF TIMES OR JUST STOP????*/
	while (philo->meals < philo->data->opt_eat)
	{
		think(philo);
		pthread_mutex_lock(fork1);
		message(philo->data->start_time, philo->spot, 0);
		pthread_mutex_lock(fork2);
		message(philo->data->start_time, philo->spot, 0);
		eat(philo, fork1, fork2);
		shleep(philo);
	}
	return (0);
}
