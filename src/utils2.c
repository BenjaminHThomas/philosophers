/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:02:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/01 08:30:31 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	signal_stop(t_table *data)
{
	pthread_mutex_lock(&data->data_mutex);
	data->must_stop = 1;
	pthread_mutex_unlock(&data->data_mutex);
}

bool	is_stopped(t_table *data)
{
	bool	retval;

	pthread_mutex_lock(&data->data_mutex);
	retval = data->must_stop;
	pthread_mutex_unlock(&data->data_mutex);
	return (retval);
}

bool	is_dead(t_philo *philo)
{
	time_t	curr_time;
	time_t	time_to_die;
	time_t	last_ate;

	time_to_die = philo->table->time_to_die;
	curr_time = get_timestamp(philo->table);
	pthread_mutex_lock(&philo->self_mutex);
	last_ate = philo->last_ate;
	pthread_mutex_unlock(&philo->self_mutex);
	if (curr_time - last_ate >= time_to_die)
	{
		if (!is_stopped(philo->table))
		{
			printf("%s",RED);
			printf("%ld %d is dead\n", curr_time, philo->idx + 1);
			signal_stop(philo->table);
		}
		return (1);
	}
	return (0);
}

void	lock_forks(t_philo *philo)
{
	if (philo->idx % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, "has taken left fork");
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, "has taken right fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, "has taken left fork");
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}
