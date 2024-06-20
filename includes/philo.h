/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 18:33:57 by bthomas          ###   ########.fr       */
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
# define MAXINT 2147483647
# define MAXUINT 4294967295

typedef struct s_data
{
	unsigned int		num_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		num_eats_each;
	pthread_mutex_t		forks[200];
	long				ts_last_ate[200];
	long				start_time;
	int					dead_philo;
}	t_data;

int				valid_input(int ac, char **av);
void			cleanup(t_data *data);
int				init(int ac, char **av, t_data *data);
unsigned int	ft_utoi(char *s);
int				ft_strlen(char *s);
long			get_milisecs(struct timeval *tv);
long			get_timestamp(t_data *data);
int				is_dead(t_data *data, int idx);

#endif
