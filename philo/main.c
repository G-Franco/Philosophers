/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:02:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/27 10:48:02 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_usage(void)
{
	printf("Usage ./philo\n"
		"number_of_philosophers (int)\n"
		"time_to_die (ms)\n"
		"time_to_eat (ms)\n"
		"time_to_sleep (ms)\n"
		"[number_of_times_each_philosopher_must_eat] (int)\n");
	return (1);
}

int	usage(int ac, char **av, t_philos *data)
{
	if (ac < 5 || ac > 6 || !av[1] || !av[2] || !av[3] || !av[4])
		return (write_usage());
	data->n = ft_atoi(av[1]);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	if (av[5])
		data->opt_eat = ft_atoi(av[5]);
	else
		data->opt_eat = 0;
	if (data->n < 1 || data->ttdie <= 0 || data->tteat <= 0
		|| data->ttsleep <= 0 || data->opt_eat < 0)
		return (write_usage());
	data->sim_start = 0;
	return (0);
}

int	prep_data(t_philos *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		if (pthread_create(&data->philos[i], 0, simulation(), 0))
			return (1);
		if (pthread_mutex_init(&data->forks[i]->fork_mutex, 0))
			return (2);
		data->forks[i]->request = 0;
	}
	data->philos[i] = 0;
	data->forks[i] = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_philos	data;

	if (usage(ac, av, &data))
		return (1);
	data.philos = (pthread_t **)malloc(sizeof(pthread_t *) * (data.n + 1));
	data.forks = (t_forks **)malloc(sizeof(t_forks *) * (data.n + 1));
	if (!data.philos || !data.forks)
		return (2);
	if (prep_data(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
