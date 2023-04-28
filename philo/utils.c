/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:24 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/28 09:48:09 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	nbr;
	int	i;
	int	sig;

	nbr = 0;
	i = 0;
	sig = 1;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sig);
}

int	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		pthread_mutex_destroy(&data->forks[i]->fork_mutex);
		free(data->forks[i]);
		free(data->philo[i]);
	}
	free(data->philo);
	free(data->forks);
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * (unsigned long)1000
		+ (time.tv_usec / (unsigned long)1000));
}
