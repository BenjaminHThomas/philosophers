/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:37:26 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/23 12:34:32 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	neighbours_can_eat(unsigned int i, t_data *data)
{
	unsigned int	left;
	unsigned int	right;

	left = (i + data->num_philo - 1) % data->num_philo;
	right = (i + 1) % data->num_philo;
	if (data->can_eat[left] || data->can_eat[right])
		return (1);
	return (0);
}

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
		if (!data->is_sleeping[i] && !data->can_eat[i]
			&& !neighbours_can_eat(i, data)
			&& !is_finished(data, i)
			&& data->ts_last_ate[i] < min_val)
		{
			hungriest = i;
			min_val = data->ts_last_ate[i];
		}
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (hungriest);
}

/* need to alter this logic to stagger better */
void	*waiter(void *waiter_data)
{
	t_data	*data;
	int		hungriest;

	data = (t_data *)waiter_data;
	if (data->num_philo == 1)
		return (NULL);
	while (!data->dead_philo && !all_finished(data))
	{
		hungriest = get_hungriest(data);
		if (hungriest != -1)
		{
			pthread_mutex_lock(&data->data_mutex);
			data->can_eat[hungriest] = 1;
			pthread_mutex_unlock(&data->data_mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
