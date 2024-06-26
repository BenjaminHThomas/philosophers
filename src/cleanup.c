/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:03 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:25:17 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->fork_mutex_init[i])
			pthread_mutex_destroy(&data->forks[i]);
		if (data->philos[i].self_mutex_init)
			pthread_mutex_destroy(&data->philos[i].self_mutex);
		i++;
	}
}
