/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/15 13:10:18 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*Writes given message*/
void	message(t_philo *philo, int n, char *msg)
{
	sem_wait(philo->data->write_s);
	printf("%lu %i %s\n", get_time() - philo->data->start_time, n + 1, msg);
	sem_post(philo->data->write_s);
	return ;
}

/*Returns current time in ms*/
time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

/*Calculates how long it needs to wait before starting simulation
and sleeps for that duration*/
void	sync_start(t_data *data)
{
	time_t	wait;

	wait = data->start_time - get_time();
	if (wait > 0)
		usleep(wait * 1000);
	return ;
}

/*Unlinks used semaphores*/
void	sem_clean(void)
{
	sem_unlink("/forks_s");
	sem_unlink("/write_s");
	sem_unlink("/last_s");
}

/*Frees everything*/
int	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		free(data->philo[i]);
	}
	free(data->philo);
	free(data->pid);
	sem_close(data->last_s);
	sem_close(data->forks);
	sem_close(data->write_s);
	sem_clean();
	return (1);
}
