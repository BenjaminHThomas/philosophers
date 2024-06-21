/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/21 10:34:34 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_data *data, int idx)
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
	pthread_mutex_lock(&data->forks[left_fork]);
	pthread_mutex_lock(&data->forks[right_fork]);
	printf("%ld %d is eating\n", get_timestamp(data), idx);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
	data->can_eat[idx] = 0;
	data->ts_last_ate[idx] = get_timestamp(data);
}

int	philo(t_data *data, int idx)
{
	unsigned int	num_eaten;

	num_eaten = 0;
	while (1)
	{
		printf("%ld %d is thinking\n", get_timestamp(data), idx);
		while (data->can_eat[idx] == 0)
			if (is_dead(data, idx))
				return (1);
		eat(data, idx);
		num_eaten++;
		printf("%ld %d is sleeping\n", get_timestamp(data), idx);
		data->is_sleeping[idx] = 1;
		usleep(data->time_to_sleep * 1000);
		data->is_sleeping[idx] = 0;
		if (data->num_eats_each && data->num_eats_each == num_eaten)
			break ;
	}
	return (0);
}
