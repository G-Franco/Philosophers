/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:02:59 by gacorrei          #+#    #+#             */
/*   Updated: 2023/08/23 15:22:17 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*Initialises everything*/
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
	sem_unlink("/last_s");
	sem_unlink("/forks_s");
	sem_unlink("/write_s");
	data->forks = sem_open("/forks_s", O_CREAT, 0644, data->n);
	data->write_s = sem_open("/write_s", O_CREAT, 0644, 1);
	data->last_s = sem_open("/last_s", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->write_s == SEM_FAILED
		|| data->last_s == SEM_FAILED)
		return (1);
	return (0);
}

/*Sets simulation start time, creates child processes and starts simulation*/
int	start(t_data *data)
{
	int		i;

	i = -1;
	data->start_time = get_time() + (data->n * 2);
	while (++i < data->n)
	{
		data->philo[i]->last_meal = data->start_time;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (1);
		else if (!data->pid[i])
			simulation(data->philo[i]);
	}
	return (0);
}

/*Waits for any process that exits with an error (1).
If any does exit with an error, every process is killed*/
void	close_sim(t_data *data)
{
	int	i;
	int	value;

	i = -1;
	while (++i < data->n)
	{
		waitpid(-1, &value, 0);
		if (value != 0)
		{
			i = -1;
			while (++i < data->n)
				kill(data->pid[i], SIGTERM);
			break ;
		}
	}
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
	data.pid = (pid_t *)malloc(sizeof(pid_t) * (data.n));
	if (!data.philo || !data.pid)
		return (free_data(&data));
	i = -1;
	while (++i < data.n)
	{
		data.philo[i] = (t_philo *)malloc(sizeof(t_philo));
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
