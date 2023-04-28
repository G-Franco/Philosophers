/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:47:51 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/28 15:39:37 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (pthread_mutex_lock(fork1))
	{
		printf("Philo %i can't grab fork1\n", philo->spot);
		return (1);
	}
	printf("Philo %i grabbed fork1\n", philo->spot);
	if (pthread_mutex_lock(fork2))
	{
		pthread_mutex_unlock(fork1);
		printf("Philo %i released fork1 because fork2 was being used\n", philo->spot);
		return (2);
	}
	printf("Philo %i grabbed both forks\n", philo->spot);
	return (0);
}

void	think(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = philo->data->forks[philo->spot];
	if (philo->spot == 0)
		fork2 = philo->data->forks[philo->data->n - 1];
	else
		fork2 = philo->data->forks[philo->spot - 1];
	while (1)
	{
		if (forks(philo, fork1, fork2))
			continue ;
		eat(philo, fork1, fork2);
		break ;
	}
	return ;
}

void	eat(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	usleep(philo->data->tteat * 1000);
	printf("Philo %i finished eating and released both forks\n", philo->spot);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	shleep(philo);
	philo->meals++;
	return ;
}

void	shleep(t_philo *philo)
{
	usleep(philo->data->ttsleep * 1000);
	return ;
}

void	*simulation(void *philos)
{
	t_philo			*philo;

	philo = (t_philo *)philos;
	philo->last_meal = get_time();
	/*CHECK IF THIS IS ALLOWED!!!*/
	if (!(philo->spot % 2))
		shleep(philo);
	while (philo->meals < philo->data->opt_eat)
		think(philo);
	return (0);
}
