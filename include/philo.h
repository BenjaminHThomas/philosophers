/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/01 08:19:54 by bento            ###   ########.fr       */
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
# include <limits.h>
# include <stdbool.h>

typedef struct s_table	t_table;

typedef enum e_philo_state
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING
}	t_philo_state;

typedef struct s_philo
{
	unsigned int		idx;
	unsigned int		left_fork;
	unsigned int		right_fork;
	time_t				last_ate;
	t_philo_state		state;
	pthread_mutex_t		self_mutex;
	bool				self_mutex_init;
	bool				is_dead;
	pthread_t			thread;
	t_table				*table;
	unsigned int		num_eaten;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t		data_mutex;
	bool				data_mutex_init;
	unsigned int		num_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					eat_limit;
	pthread_mutex_t		forks[200];
	bool				fork_mutex_init[200];
	struct s_philo		philos[200];
	time_t				start_time;
	bool				must_stop;
	pthread_t			hangman_thread;
}	t_table;

int				valid_input(int ac, char **av);
void			cleanup(t_table *data);
int				init(int ac, char **av, t_table *data);
unsigned int	ft_utoi(char *s);
long			get_milisecs(struct timeval *tv);
long			get_timestamp(t_table *data);
void			*philo_life(void *philo_data);
int				is_finished(t_table *data, int idx);
int				all_finished(t_table *data);
void			philo_wait(t_table *data, unsigned int msecs);
void			print_state(t_philo *philo, char *status);
void			lock_forks(t_philo *philo);
void			unlock_forks(t_philo *philo);
int				ft_errmsg(const char *s);
bool			is_dead(t_philo *philo);
void			*hangman(void *arg);
bool			is_stopped(t_table *data);

#endif
