/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:24 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/08 14:01:10 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_int(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

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
		pthread_mutex_destroy(data->forks[i]);
		pthread_mutex_destroy(&data->philo[i]->last_m);
		pthread_mutex_destroy(&data->philo[i]->counter_m);
		free(data->forks[i]);
		free(data->philo[i]);
	}
	pthread_mutex_destroy(&data->write_m);
	pthread_mutex_destroy(&data->end_m);
	free(data->philo);
	free(data->forks);
	return (1);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

pthread_mutex_t	*forks(t_philo *philo, int fork_n)
{
	if (fork_n == 1)
	{
		if (philo->spot % 2)
			return (philo->data->forks[philo->spot]);
		else
			return (philo->data->forks[(philo->spot + 1) % philo->data->n]);
	}
	else
	{
		if (philo->spot % 2)
			return (philo->data->forks[(philo->spot + 1) % philo->data->n]);
		else
			return (philo->data->forks[philo->spot]);
	}
}
