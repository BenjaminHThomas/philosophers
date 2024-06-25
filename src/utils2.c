/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:02:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 21:09:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_wait(t_data *data, unsigned int msecs)
{
	long		curr_time;
	long long	time_to_rest;

	time_to_rest = msecs;
	curr_time = get_timestamp(data);
	while (get_timestamp(data) - curr_time < time_to_rest)
	{
		usleep(1000);
		if (data->dead_philo)
			break ;
	}
}

void	lock_forks(t_data *data, int left_fork, int right_fork, int idx)
{
	if (idx % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[left_fork]);
		pthread_mutex_lock(&data->forks[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[right_fork]);
		pthread_mutex_lock(&data->forks[left_fork]);
	}
}

void	unlock_forks(t_data *data, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
}

int	is_dead(t_data *data, int idx)
{
	long	curr_time;

	curr_time = get_timestamp(data);
	if (curr_time - data->ts_last_ate[idx] >= data->time_to_die)
	{
		if (!data->dead_philo)
		{
			printf("%ld %d is dead\n", curr_time, idx + 1);
			data->dead_philo = 1;
		}
		return (1);
	}
	return (0);
}
