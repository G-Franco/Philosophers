/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:57:11 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/02 13:24:42 by gacorrei         ###   ########.fr       */
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

struct	s_data;
typedef struct s_philo
{
	pthread_t			id;
	pthread_t			status;
	pthread_mutex_t		last_meal_m;
	unsigned long		last_meal;
	struct s_data		*data;
	int					meals;
	int					spot;
}						t_philo;

typedef struct s_data
{
	t_philo			**philo;
	pthread_mutex_t	**forks;
	pthread_mutex_t	write;
	pthread_mutex_t	meals;
	pthread_mutex_t	end_m;
	unsigned long	ttdie;
	unsigned long	tteat;
	unsigned long	ttsleep;
	unsigned long	start_time;
	int				n;
	int				end;
	int				opt_eat;
	int				philos_full;
}					t_data;

/*main.c*/
int				write_usage(void);
int				usage(int ac, char **av, t_data *data);
int				prep_data(t_data *data);
int				start(t_data *data);

/*simulation.c*/
void			*status(void *philo);
void			life(t_philo *philo, pthread_mutex_t *fork1,
					pthread_mutex_t *fork2);
void			*single(t_philo *philo, pthread_mutex_t *fork1);
void			*simulation(void *philo);

/*utils.c*/
void			message(t_philo *philo,	int n, char *msg, int flag);
int				check_int(int ac, char **av);
int				ft_atoi(char *str);
int				free_data(t_data *data);
unsigned long	get_time(void);

/*utils2*/
int				end_check(t_philo *philo);
void			end(t_philo *philo);

#endif