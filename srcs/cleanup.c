/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:03 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 17:28:59 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	unsigned int	i;

	if (data->data_mutex_init)
		pthread_mutex_destroy(&data->data_mutex);
	i = 0;
	while (i < data->num_philo)
	{
		if (data->fork_mutex_init[i])
			pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
