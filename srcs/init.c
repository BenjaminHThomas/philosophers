/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/21 10:31:24 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	memset(data->can_eat, 0, sizeof(data->can_eat));
	memset(data->is_sleeping, 0, sizeof(data->is_sleeping));
	gettimeofday(&tv, NULL);
	data->start_time = get_milisecs(&tv);
	return (0);
}
