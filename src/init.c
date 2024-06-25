/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 19:22:39 by bthomas          ###   ########.fr       */
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
	return (0);
}

int	init_mutexs(t_data *data)
{
	unsigned int	i;

	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (1);
	data->data_mutex_init = 1;
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		data->fork_mutex_init[i] = 1;
		i++;
	}
	return (0);
}

int	init(int ac, char **av, t_data *data)
{
	struct timeval	tv;

	memset(data, 0, sizeof(t_data));
	data->num_philo = ft_utoi(av[1]);
	data->time_to_die = ft_utoi(av[2]);
	data->time_to_eat = ft_utoi(av[3]);
	data->time_to_sleep = ft_utoi(av[4]);
	if (ac == 6)
		data->num_eats_each = ft_utoi(av[5]);
	else
		data->num_eats_each = 0;
	if (init_mutexs(data))
		return (1);
	gettimeofday(&tv, NULL);
	data->start_time = get_milisecs(&tv);
	return (create_threads(data));
}
