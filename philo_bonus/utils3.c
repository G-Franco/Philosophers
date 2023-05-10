/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:32 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/10 14:24:11 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sync_start(t_data *data)
{
	time_t	wait;

	wait = data->start_time - get_time();
	if (wait > 0)
		usleep(wait * 1000);
	return ;
}
