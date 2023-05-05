/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:02:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/05 14:34:25 by gacorrei         ###   ########.fr       */
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
		"[number_of_times_each_philosopher_must_eat] (int)\n"
		"Use only positive values!\n");
	return (1);
}

int	usage(int ac, char **av, t_data *data)
{
	if (check_int(ac, av))
		return (write_usage());
	if (ac < 5 || ac > 6 || !av[1] || !av[2] || !av[3] || !av[4])
		return (write_usage());
	data->n = ft_atoi(av[1]);
	data->ttdie = (unsigned long)ft_atoi(av[2]);
	data->tteat = (unsigned long)ft_atoi(av[3]);
	data->ttsleep = (unsigned long)ft_atoi(av[4]);
	if (av[5])
		data->opt_eat = ft_atoi(av[5]);
	else
		data->opt_eat = 0;
	if (data->n < 1 || data->ttdie <= 0 || data->tteat <= 0
		|| data->ttsleep <= 0 || data->opt_eat < 0)
		return (write_usage());
	return (0);
}

int	prep_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		if (pthread_mutex_init(data->forks[i], 0))
			return (1);
		if (pthread_mutex_init(&data->philo[i]->last_m, 0))
			return (1);
		if (pthread_mutex_init(&data->philo[i]->counter_m, 0))
			return (1);
		data->philo[i]->meals = 0;
		data->philo[i]->spot = i;
		data->philo[i]->data = data;
		data->philo[i]->fork1 = forks(data->philo[i], 1);
		data->philo[i]->fork2 = forks(data->philo[i], 2);
	}
	data->end = 0;
	data->philos_full = 0;
	if (pthread_mutex_init(&data->write_m, 0))
		return (1);
	if (pthread_mutex_init(&data->end_m, 0))
		return (1);
	return (0);
}

int	start(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time() + (data->n * 2);
	while (++i < data->n)
	{
		if (pthread_create(&data->philo[i]->id, 0, simulation, data->philo[i]))
			return (1);
	}
	if (data->n > 1)
		status(data);
	i = -1;
	while (++i < data->n)
		pthread_join(data->philo[i]->id, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (usage(ac, av, &data))
		return (1);
	i = -1;
	data.philo = (t_philo **)malloc(sizeof(t_philo *) * (data.n));
	data.forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (data.n));
	if (!data.philo || !data.forks)
		return (free_data(&data));
	i = -1;
	while (++i < data.n)
	{
		data.philo[i] = (t_philo *)malloc(sizeof(t_philo));
		data.forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data.philo[i] || !data.forks[i])
			return (free_data(&data));
	}
	if (prep_data(&data))
		return (free_data(&data));
	if (start(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
