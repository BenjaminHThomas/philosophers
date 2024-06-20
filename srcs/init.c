/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 12:03:25 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int idx)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(*philo));
	philo->idx = idx;
	pthread_mutex_init(&philo->fork, NULL);
	return (philo);
}

int	init(int ac, char **av, t_data *data)
{
	t_philo			*next;
	unsigned int	i;

	memset(data, 0, sizeof(*data));
	data->num_philo = ft_utoi(av[1]);
	data->time_to_die = ft_utoi(av[2]);
	data->time_to_eat = ft_utoi(av[3]);
	data->time_to_sleep = ft_utoi(av[4]);
	if (ac == 6)
		data->num_eats_each = ft_utoi(av[5]);
	data->head = new_philo(0);
	if (!data->head)
		return (1);
	i = 1;
	next = data->head;
	while (i < data->num_philo)
	{
		next = new_philo(i);
		if (!next)
			return (1);
		ft_add_philo(&data->head, next);
		i++;
	}
	return (0);
}
