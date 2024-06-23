/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 18:59:08 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_data *data, int left_fork, int right_fork, int idx)
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

static int	is_dead(t_data *data, int idx)
{
	if (get_timestamp(data) - data->ts_last_ate[idx] >= data->time_to_die)
	{
		printf("%ld %d is dead\n", get_timestamp(data), idx);
		data->dead_philo = 1;
		return (1);
	}
	return (0);
}

static void	eat(t_data *data, int idx, unsigned int *num_eaten)
{
	int	left_fork;
	int	right_fork;

	if (data->dead_philo)
		return ;
	left_fork = idx;
	right_fork = (idx + 1) % data->num_philo;
	lock_forks(data, left_fork, right_fork, idx);
	printf("%ld %d is eating\n", get_timestamp(data), idx);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
	pthread_mutex_lock(&data->data_mutex);
	data->can_eat[idx] = 0;
	data->ts_last_ate[idx] = get_timestamp(data);
	(*num_eaten)++;
	pthread_mutex_unlock(&data->data_mutex);
}

static void	sleep_philo(t_data *data, int idx)
{
	if (data->dead_philo)
		return ;
	printf("%ld %d is sleeping\n", get_timestamp(data), idx);
	data->is_sleeping[idx] = 1;
	usleep(data->time_to_sleep * 1000);
	data->is_sleeping[idx] = 0;
}

void	*philo(void *philo_data)
{
	unsigned int	num_eaten;
	unsigned int	idx;
	t_data			*data;

	num_eaten = 0;
	idx = ((struct s_philo *)philo_data)->idx;
	data = ((struct s_philo *)philo_data)->data;
	while (data->dead_philo == 0)
	{
		printf("%ld %d is thinking\n", get_timestamp(data), idx);
		while (data->can_eat[idx] == 0 && data->dead_philo == 0)
		{
			if (is_dead(data, idx))
				break ;
			usleep(500);
		}
		eat(data, idx, &num_eaten);
		sleep_philo(data, idx);
		if (data->num_eats_each && data->num_eats_each == num_eaten)
			break ;
	}
	pthread_mutex_lock(&data->data_mutex);
	data->finished_eating++;
	pthread_mutex_unlock(&data->data_mutex);
	return (NULL);
}
