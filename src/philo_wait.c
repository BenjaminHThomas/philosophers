/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:02:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 10:26:50 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_wait(t_data *data, unsigned int msecs)
{
	long		curr_time;
	long long	time_to_rest;

	time_to_rest = msecs;
	curr_time = get_timestamp(data);
	while (get_timestamp(data) - curr_time < time_to_rest)
	{
		usleep(1000);
		if (data->dead_philo)
			break ;
	}
}
