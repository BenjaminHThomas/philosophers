/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:50:04 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/21 10:33:53 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_utoi(char *s)
{
	int				i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (s && (s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s && s[i] == '+')
		i++;
	while (s && (s[i] >= '0' && s[i] <= '9'))
	{
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	return (res);
}

long	get_milisecs(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

long	get_timestamp(t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (data->start_time - get_milisecs(&now));
}

int	get_hungriest(t_data *data)
{
	unsigned int		i;
	unsigned int		max;
	long				max_val;

	i = 0;
	max_val = 0;
	while (i < data->num_philo)
	{
		if (data->ts_last_ate[i] > max_val)
		{
			max = i;
			max_val = data->ts_last_ate[i];
		}
		i++;
	}
	return (max);
}

int	get_next_hungriest(t_data *data, int bigger_idx)
{
	long				curr_val;
	long				prev_max;
	long				new_max;
	unsigned int		i;
	unsigned int		max;

	prev_max = data->ts_last_ate[bigger_idx];
	i = 0;
	max = 0;
	new_max = 0;
	while (i < data->num_philo)
	{
		curr_val = data->ts_last_ate[i];
		if (curr_val < prev_max && curr_val > new_max)
		{
			new_max = curr_val;
			max = i;
		}
		i++;
	}
	return (max);
}
