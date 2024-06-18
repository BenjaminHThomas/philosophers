/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/18 16:28:13 by bthomas          ###   ########.fr       */
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

typedef struct s_philo
{
	int					idx;
	int					fork;
	pthread_mutex_t		mutex;
	struct s_philo		*next;
}	t_philo;

typedef struct s_data
{
	unsigned int	num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eats_each;
	t_philo	*head;
}	t_data;

int	valid_input(int	ac, char **av);
int	cleanup(t_data *data);
int	init(int ac, char **av, t_data *data);

#endif
