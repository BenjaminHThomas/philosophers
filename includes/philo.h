/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 11:55:48 by bthomas          ###   ########.fr       */
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

typedef struct s_philo
{
	int					idx;
	int					ntimes_eaten;
	int					time_till_death;
	int					dur_eating;
	int					dur_sleeping;
	pthread_mutex_t		fork;
	struct s_philo		*next;
}	t_philo;

typedef struct s_data
{
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eats_each;
	t_philo			*head;
}	t_data;

int				valid_input(int ac, char **av);
int				cleanup(t_data *data);
int				init(int ac, char **av, t_data *data);
unsigned int	ft_utoi(char *s);
void			ft_add_philo(t_philo **head, t_philo *new);
void			ft_clear_philos(t_data *data);

#endif
