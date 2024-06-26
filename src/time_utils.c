/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:04:51 by bento             #+#    #+#             */
/*   Updated: 2024/06/26 19:06:18 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_milisecs(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

long	get_timestamp(t_table *data)
{
	struct timeval	now;
	long			currtime;

	gettimeofday(&now, NULL);
	currtime = get_milisecs(&now);
	return (currtime - data->start_time);
}

void	philo_wait(t_table *data, unsigned int msecs)
{
	long		curr_time;
	long long	time_to_rest;

	time_to_rest = msecs;
	curr_time = get_timestamp(data);
	while (get_timestamp(data) - curr_time < time_to_rest)
	{
		usleep(1000);
		if (data->must_stop)
			break ;
	}
}