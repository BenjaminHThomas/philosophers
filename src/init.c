/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/30 09:08:25 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *data)
{
	unsigned int		i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].table = data;
		data->philos[i].idx = i;
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_life, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&data->hangman_thread, NULL, hangman, data) != 0)
		return (1);
	return (0);
}

int	init_mutexs(t_table *data)
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
		if (pthread_mutex_init(&data->philos[i].self_mutex, NULL) != 0)
			return (1);
		data->philos[i].self_mutex_init = 1;
		i++;
	}
	return (0);
}

int	init(int ac, char **av, t_table *data)
{
	struct timeval	tv;

	memset(data, 0, sizeof(t_table));
	data->num_philo = ft_utoi(av[1]);
	data->time_to_die = ft_utoi(av[2]);
	data->time_to_eat = ft_utoi(av[3]);
	data->time_to_sleep = ft_utoi(av[4]);
	if (ac == 6)
		data->eat_limit = ft_utoi(av[5]);
	else
		data->eat_limit = -1;
	if (init_mutexs(data))
		return (1);
	gettimeofday(&tv, NULL);
	data->start_time = get_milisecs(&tv);
	return (create_threads(data));
}
