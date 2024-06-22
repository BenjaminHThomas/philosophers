/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 17:06:14 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	unsigned int		i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo_data[i].data = data;
		data->philo_data[i].idx = i;
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->threads[i], NULL,
				philo, &data->philo_data[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->waiter, NULL, waiter, data) != 0)
		return (1);
	return (0);
}

int	init_mutexs(t_data *data)
{
	unsigned int	i;

	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init(int ac, char **av, t_data *data)
{
	struct timeval	tv;

	data->num_philo = ft_utoi(av[1]);
	data->time_to_die = ft_utoi(av[2]);
	data->time_to_eat = ft_utoi(av[3]);
	data->time_to_sleep = ft_utoi(av[4]);
	if (ac == 6)
		data->num_eats_each = ft_utoi(av[5]);
	else
		data->num_eats_each = 0;
	data->dead_philo = 0;
	data->finished_eating = 0;
	memset(data->ts_last_ate, 0, sizeof(data->ts_last_ate));
	memset(data->can_eat, 0, sizeof(data->can_eat));
	memset(data->is_sleeping, 0, sizeof(data->is_sleeping));
	memset(data->philo_data, 0, sizeof(data->philo_data));
	if (init_mutexs(data))
		return (1);
	gettimeofday(&tv, NULL);
	data->start_time = get_milisecs(&tv);
	return (create_threads(data));
}
