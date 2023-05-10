/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:57:11 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/10 14:29:30 by gacorrei         ###   ########.fr       */
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

struct	s_data;
typedef struct s_philo
{
	struct s_data	*data;
	sem_t			*counter_s;
	sem_t			*last_s;
	int				spot;
	int				meals;
	time_t			last_meal;
}					t_philo;

typedef struct s_data
{
	t_philo			**philo;
	sem_t			*forks;
	sem_t			*write_s;
	sem_t			*end_s;
	time_t			start_time;
	time_t			ttsleep;
	time_t			tteat;
	time_t			ttdie;
	pid_t			**pid;
	int				n;
	int				end;
	int				opt_eat;
}					t_data;

/*main.c*/
int		write_usage(void);
int		usage(int ac, char **av, t_data *data);
int		prep_data(t_data *data);
int		start(t_data *data);
void	close_sim(t_data *data);

/*simulation.c*/
int		status(t_data *data);
void	think(t_philo *philo);
void	life(t_philo *philo);
void	*single(t_philo *philo);
int		reopen(t_philo *philo);
void	*simulation(t_philo *philos);

/*utils.c*/
int		check_int(int ac, char **av);
int		ft_atoi(char *str);
void	sem_clean(void);
int		free_data(t_data *data);
time_t	get_time(void);

/*utils2*/
void	message(t_philo *philo, int n, char *msg, int end);
int		end_check(t_data *data);
void	end(t_data *data);
int		dead(t_philo *philo);
int		checker(t_data *data);

/*utils3*/
void	sync_start(t_data *data);


#endif