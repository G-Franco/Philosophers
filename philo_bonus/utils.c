/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:19:24 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/09 10:51:12 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	sem_clean(void)
{
	sem_unlink("/forks_s");
	sem_unlink("/write_s");
	sem_unlink("/end_s");
	sem_unlink("/counter_s");
	sem_unlink("/last_s");
}

int	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
		free(data->philo[i]);
	free(data->philo);
	sem_close(data->forks);
	sem_close(data->write_s);
	sem_close(data->end_s);
	sem_close(data->counter_s);
	sem_close(data->last_s);
	sem_clean();
	return (1);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}
