/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/30 18:36:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*status_monitor(void *philo)
{
	
}

void	think(t_philo *philo)
{
	message(philo, philo->data->start_time, philo->spot, "is thinking");
	pthread_mutex_lock(fork1);
	message(philo, philo->data->start_time, philo->spot, "has taken a fork");
	pthread_mutex_lock(fork2);
	message(philo, philo->data->start_time, philo->spot, "has taken a fork");
	return ;
}

void	eat(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	message(philo, philo->data->start_time, philo->spot, "is eating");
	philo->last_meal = get_time();
	usleep(philo->data->tteat * 1000);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	philo->meals++;
	return ;
}

void	shleep(t_philo *philo)
{
	message(philo, philo->data->start_time, philo->spot, "is sleeping");
	usleep(philo->data->ttsleep * 1000);
	return ;
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
	philo->last_meal = get_time();
	/*CHECK IF THIS IS ALLOWED!!!*/
	if (!(philo->spot % 2))
		usleep(philo->data->ttsleep * 1000);
	/*SHOULD THE PHILO KEEP IN LOOP UNTIL ALL OTHERS HAVE EATEN THE REQUIRED AMOUNT OF TIMES OR JUST STOP????*/
	while (philo->meals < philo->data->opt_eat)
	{
		think(philo);
		eat(philo, fork1, fork2);
		shleep(philo);
	}
	return (0);
}
