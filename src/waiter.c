/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:37:26 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/25 19:19:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	neighbours_can_eat(unsigned int i, t_data *data)
{
	unsigned int	left;
	unsigned int	right;
	int				retval;

	left = (i + data->num_philo - 1) % data->num_philo;
	right = (i + 1) % data->num_philo;
	retval = (data->can_eat[left] || data->can_eat[right]);
	return (retval);
}

int	is_safe(t_data *data, unsigned int idx)
{
	int	retval;

	retval = (!data->is_sleeping[idx]
			&& !is_finished(data, idx));
	return (retval);
}
/*
static int	get_hungriest(t_data *data)
{
	unsigned int	i;
	unsigned int	hungriest;
	long			min_val;

	i = 0;
	min_val = MAXINT;
	hungriest = -1;
	while (i < data->num_philo)
	{
		if (is_safe(data, i) && data->ts_last_ate[i] < min_val)
		{
			hungriest = i;
			min_val = data->ts_last_ate[i];
		}
		i++;
		usleep(15);
	}
	return (hungriest);
}
*/
/*
void	*waiter(void *waiter_data)
{
	t_data	*data;
	int		hungriest;

	data = (t_data *)waiter_data;
	if (data->num_philo <= 1)
		return (NULL);
	while (!data->dead_philo && !all_finished(data))
	{
		hungriest = get_hungriest(data);
		if (hungriest != -1)
			data->can_eat[get_hungriest(data)] = 1;
	}
	return (NULL);
}
*/
