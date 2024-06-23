/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:37:26 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 18:58:11 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_hungriest(t_data *data)
{
	unsigned int		i;
	unsigned int		hungriest;
	long				min_val;

	i = 0;
	min_val = MAXINT;
	hungriest = -1;
	pthread_mutex_lock(&data->data_mutex);
	while (i < data->num_philo)
	{
		if (!data->is_sleeping[i] && !data->can_eat[i] &&
			!data->can_eat[(i + 1) % data->num_philo] &&
			!data->can_eat[(i + data->num_philo - 1) % data->num_philo] &&
			data->ts_last_ate[i] < min_val)
		{
			hungriest = i;
			min_val = data->ts_last_ate[i];
		}
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (hungriest);
}

/* need to alter this logic to stagger the approvals 
 * currently it's marking it all as yes every time*/
void	*waiter(void *waiter_data)
{
	t_data	*data;
	int		hungriest;

	data = (t_data *)waiter_data;
	if (data->num_philo == 1)
		return (NULL);
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
		usleep(10000);
	}
	return (NULL);
}
