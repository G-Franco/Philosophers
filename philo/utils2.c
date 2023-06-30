/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/06/30 17:20:40 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Checks if the simulation has finished and writes message for current philo.
if the end flag is 1 or end_check is true no message is written.
end flag is only passed when the message is for a dead philo so that
the end_checker is not executed unnecessarily*/
void	message(t_philo *philo, int n, char *msg, int end)
{
	pthread_mutex_lock(&philo->data->write_m);
	if (!end && end_check(philo->data))
	{
		pthread_mutex_unlock(&philo->data->write_m);
		return ;
	}
	printf("%lu %i %s\n", get_time() - philo->data->start_time, n + 1, msg);
	pthread_mutex_unlock(&philo->data->write_m);
	return ;
}

/*Checks if simulation has finished*/
int	end_check(t_data *data)
{
	pthread_mutex_lock(&data->end_m);
	if (data->end)
	{
		pthread_mutex_unlock(&data->end_m);
		return (1);
	}
	pthread_mutex_unlock(&data->end_m);
	return (0);
}

/*Sets flag to stop simulation*/
void	end(t_data *data)
{
	pthread_mutex_lock(&data->end_m);
	data->end = 1;
	pthread_mutex_unlock(&data->end_m);
	return ;
}

/*Calculates time since last meal, if it's more than ttdie
the death message is written and the simulation is set to finished*/
int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_m);
	if (get_time() - philo->last_meal
		>= philo->data->ttdie2)
	{
		end(philo->data);
		message(philo, philo->spot, "died", 1);
		pthread_mutex_unlock(&philo->last_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_m);
	return (0);
}

/*Runs the death checker for every philo and
if there is a limit for eating it also check is all philos
have eaten the required amount of times*/
int	checker(t_data *data)
{
	int		philos_full;
	int		i;

	i = -1;
	philos_full = 1;
	while (++i < data->n)
	{
		if (dead(data->philo[i]))
			return (1);
		if (!data->opt_eat)
			continue ;
		pthread_mutex_lock(&data->philo[i]->counter_m);
		if (data->philo[i]->meals < data->opt_eat)
			philos_full = 0;
		pthread_mutex_unlock(&data->philo[i]->counter_m);
	}
	if (data->opt_eat && philos_full == 1)
	{
		end(data);
		return (1);
	}
	return (0);
}
