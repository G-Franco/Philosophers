/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:02:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/10 14:30:40 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		data->philo[i]->meals = 0;
		data->philo[i]->spot = i;
		data->philo[i]->data = data;
	}
	data->end = 0;
	data->forks = sem_open("/forks_s", O_CREAT, 0644, data->n);
	data->write_s = sem_open("/write_s", O_CREAT, 0644, 1);
	data->end_s = sem_open("/end_s", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->write_s == SEM_FAILED
		|| data->end_s == SEM_FAILED)
		return (1);
	return (0);
}

int	start(t_data *data)
{
	int		i;
	pid_t	pid;

	i = -1;
	data->start_time = get_time() + (data->n * 2);
	while (++i < data->n)
	{
		data->philo[i]->last_meal = data->start_time;
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid > 0)
			data->pid[i] = &pid;
		else if (!pid)
			simulation(data->philo[i]);
	}
	if (data->n > 1)
		status(data);
	return (0);
}

void	close_sim(t_data *data)
{
	int	i;

	sync_start(data);
	i = -1;
	while (++i < data->n)
		waitpid(*(data->pid[i]), 0, 0);
	return ;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (usage(ac, av, &data))
		return (1);
	i = -1;
	data.philo = (t_philo **)malloc(sizeof(t_philo *) * (data.n));
	data.pid = (pid_t **)malloc(sizeof(pid_t *) * (data.n));
	if (!data.philo)
		return (free_data(&data));
	i = -1;
	while (++i < data.n)
	{
		data.philo[i] = (t_philo *)malloc(sizeof(t_philo));
		data.pid[i] = (pid_t *)malloc(sizeof(pid_t));
		if (!data.philo[i])
			return (free_data(&data));
	}
	if (prep_data(&data))
		return (free_data(&data));
	if (start(&data))
		return (free_data(&data));
	close_sim(&data);
	free_data(&data);
	return (0);
}
