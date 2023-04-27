/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:57:11 by gacorrei          #+#    #+#             */
/*   Updated: 2023/04/27 10:51:18 by gacorrei         ###   ########.fr       */
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

typedef struct s_philos
{
	pthread_t	**philos;
	t_forks		**forks;
	int			n;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			opt_eat;
	int			sim_start;
}				t_philos;

/*main.c*/
int		write_usage(void);
int		usage(int ac, char **av, t_philos *data);
int		prep_data(t_philos *data);

/*utils.c*/
int		ft_atoi(char *str);
int		free_data(t_philos *data);
void	*simulation(void);

#endif