/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 21:19:39 by bthomas          ###   ########.fr       */
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

void	unlock_forks(t_data *data, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
}

static int	is_dead(t_data *data, int idx)
{
	long	currtime;

	currtime = get_timestamp(data);
	if (currtime - data->ts_last_ate[idx] >= data->time_to_die)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (!data->dead_philo)
		{
			printf("%ld %d is dead\n", currtime, idx + 1);
			data->dead_philo = 1;
		}
		pthread_mutex_unlock(&data->data_mutex);
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
	lock_forks(data, left_fork, right_fork, idx);
	if (is_dead(data, idx) || data->dead_philo)
	{
		unlock_forks(data, left_fork, right_fork);
		return ;
	}
	data->ts_last_ate[idx] = get_timestamp(data);
	printf("%ld %d is eating\n", get_timestamp(data), idx + 1);
	philo_wait(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
	data->can_eat[idx] = 0;
	data->num_eaten[idx]++;
}

static void	sleep_philo(t_data *data, int idx)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->dead_philo)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->data_mutex);
	printf("%ld %d is sleeping\n", get_timestamp(data), idx + 1);
	data->is_sleeping[idx] = 1;
	philo_wait(data, data->time_to_sleep);
	data->is_sleeping[idx] = 0;
}

void	*philo(void *philo_data)
{
	unsigned int	idx;
	t_data			*data;

	idx = ((struct s_philo *)philo_data)->idx;
	data = ((struct s_philo *)philo_data)->data;
	data->ts_last_ate[idx] = get_timestamp(data);
	if (data->num_philo == 1)
	{
		printf("%ld %d is thinking\n", get_timestamp(data), idx + 1);
		philo_wait(data, data->time_to_die);
		is_dead(data, idx);
	}
	if (idx % 2 == 0)
		philo_wait(data, 60);
	while (data->dead_philo == 0)
	{
		printf("%ld %d is thinking\n", get_timestamp(data), idx + 1);
		eat(data, idx);
		sleep_philo(data, idx);
		if (data->num_eats_each && data->num_eats_each == data->num_eaten[idx])
			break ;
	}
	return (NULL);
}
