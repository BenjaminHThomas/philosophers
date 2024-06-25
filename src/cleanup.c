/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:03 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 19:21:46 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (data->fork_mutex_init[i])
			pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
