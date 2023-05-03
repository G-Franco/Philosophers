/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/02 13:19:19 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	if (philo->data->end)
		return (1);
	pthread_mutex_unlock(&philo->data->end_m);
	return (0);
}

void	end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->end_m);
	return ;
}

void	shleep(t_philo *philo, time_t time)
{
	time_t	wait;

	wait = get_time() + time;
	while (get_time() < wait)
	{
		if (end_check(philo))
			return ;
		usleep(5000);
	}
	return ;
}
