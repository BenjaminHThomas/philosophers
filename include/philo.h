/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 19:22:31 by bthomas          ###   ########.fr       */
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
# define MAXUINT 4294967295
# define MAXINT 2147483647
# define MININT -2147483648

struct s_philo
{
	struct s_data	*data;
	unsigned int	idx;
};

typedef struct s_data
{
	pthread_mutex_t		data_mutex;
	int					data_mutex_init;
	unsigned int		num_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		num_eats_each;
	pthread_mutex_t		forks[200];
	int					fork_mutex_init[200];
	pthread_t			threads[200];
	struct s_philo		philo_data[200];
	int					is_sleeping[200];
	int					can_eat[200];
	long				ts_last_ate[200];
	unsigned int		num_eaten[200];
	long				start_time;
	int					dead_philo;
}	t_data;

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
