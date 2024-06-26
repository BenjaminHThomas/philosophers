/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:08:21 by bento            ###   ########.fr       */
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

typedef struct s_table t_table;

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
	t_table				*table;
	unsigned int		num_eaten;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t		data_mutex;
	int					data_mutex_init;
	unsigned int		num_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					eat_limit;
	pthread_mutex_t		forks[200];
	int					fork_mutex_init[200];
	pthread_t			threads[200];
	struct s_philo		philos[200];
	time_t				start_time;
	bool				must_stop;
}	t_table;

int				valid_input(int ac, char **av);
void			cleanup(t_data *data);
int				init(int ac, char **av, t_data *data);
unsigned int	ft_utoi(char *s);
long			get_milisecs(struct timeval *tv);
long			get_timestamp(t_data *data);
void			*philo(void *philo_data);
void			*waiter(void *waiter_data);
int				is_finished(t_data *data, int idx);
int				all_finished(t_data *data);
void			philo_wait(t_data *data, unsigned int msecs);
int				neighbours_can_eat(unsigned int i, t_data *data);
int				is_safe(t_data *data, unsigned int idx);

#endif
