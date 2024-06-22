/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:37:26 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 17:06:49 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_hungriest(t_data *data)
{
	unsigned int		i;
	unsigned int		max;
	long				max_val;

	i = 0;
	max_val = MININT;
	max = -1;
	pthread_mutex_lock(&data->data_mutex);
	while (i < data->num_philo)
	{
		if (data->ts_last_ate[i] > max_val)
		{
			if (!data->is_sleeping[i] && !data->can_eat[i])
			{
				max = i;
				max_val = data->ts_last_ate[i];
			}
		}
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (max);
}

void	*waiter(void *waiter_data)
{
	t_data	*data;
	int		hungriest;

	data = (t_data *)waiter_data;
	while (data->dead_philo == 0
		&& data->finished_eating != data->num_philo)
	{
		hungriest = get_hungriest(data);
		if (hungriest != -1)
		{
			pthread_mutex_lock(&data->data_mutex);
			data->can_eat[hungriest] = 1;
			pthread_mutex_unlock(&data->data_mutex);
		}
		usleep(200);
	}
	return (NULL);
}
