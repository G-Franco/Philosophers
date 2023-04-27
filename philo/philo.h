/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:57:11 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/27 14:03:20 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_forks
{
	pthread_mutex_t	fork_mutex;
	int				request;
}					t_forks;

typedef struct s_philo
{
	pthread_t	id;
	int			n;
	int			meals;
	int			last_meal;
}				t_philo;

typedef struct s_data
{
	t_philo		**philo;
	t_forks		**forks;
	int			n;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			opt_eat;
	int			sim_start;
}				t_data;

/*main.c*/
int		write_usage(void);
int		usage(int ac, char **av, t_data *data);
int		prep_data(t_data *data);

/*utils.c*/
int		ft_atoi(char *str);
int		free_data(t_data *data);
void	*simulation(void *philo);

#endif