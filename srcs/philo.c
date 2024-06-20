/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 18:35:19 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (data->start_time - get_milisecs(&now));
}

int	is_dead(t_data *data, int idx)
{
	if (get_timestamp(data) - data->ts_last_ate[idx] > data->time_to_die)
	{
		printf("%ld %d is dead", get_timestamp(data), idx);
		data->dead_philo = 1;
		return (1);
	}
	return (0);
}

static void	eat(t_data *data, int idx)
{
	int	left_fork;
	int	right_fork;

	left_fork = idx;
	right_fork = (idx + 1) % data->num_philo;
	pthread_mutex_lock(data->forks[left_fork]);
	pthread_mutex_lock(data->forks[right_fork]);
	printf("%ld %d is eating\n", get_timestamp(data), idx);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(data->forks[left_fork]);
	pthread_mutex_unlock(data->forks[right_fork]);
}

int	*philo(t_data *data, int idx)
{
	int		num_eaten;

	num_eaten = 0;
	while (1)
	{
		printf("%ld %d is thinking\n", get_timestamp(data), idx);
		eat(data, idx);
		data->ts_last_ate[idx] = get_timestamp(data);
		num_eaten++;
		printf("%ld %d is sleeping\n", get_timestamp(data), idx);
		usleep(data->time_to_sleep * 1000);
		if (data->num_eats_each && data->num_eats_each == times_eaten)
			break ;
	}
	return (0);
}
