/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:57:11 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/15 10:27:59 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

struct	s_data;
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		id;
	int				spot;
	int				meals;
	time_t			last_meal;
}					t_philo;

typedef struct s_data
{
	t_philo			**philo;
	sem_t			*forks;
	sem_t			*write_s;
	sem_t			*last_s;
	time_t			start_time;
	time_t			ttsleep;
	time_t			tteat;
	time_t			ttdie;
	pid_t			*pid;
	int				n;
	int				end;
	int				opt_eat;
}					t_data;

/*main.c*/
int		prep_data(t_data *data);
int		start(t_data *data);
void	close_sim(t_data *data);

/*simulation.c*/
void	*status(void *philos);
void	think(t_philo *philo);
void	life(t_philo *philo);
void	simulation(t_philo *philos);

/*utils.c*/
int		check_int(int ac, char **av);
int		ft_atoi(char *str);
int		write_usage(void);
int		usage(int ac, char **av, t_data *data);

/*utils2*/
void	message(t_philo *philo, int n, char *msg);
time_t	get_time(void);
void	sync_start(t_data *data);
void	sem_clean(void);
int		free_data(t_data *data);

#endif