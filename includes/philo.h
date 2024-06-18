/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/18 15:47:07 by bthomas          ###   ########.fr       */
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

typedef struct s_philo
{
	int					idx;
	int					fork;
	pthread_mutex_t		mutex;
	struct s_philo		*next;
}	t_philo;

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_eats_each;
	t_philo	*head;
}	t_data;

int	valid_input(int	ac, char **av);
int	cleanup(t_data *data);
int	init(int ac, char **av, t_data *data);

#endif
