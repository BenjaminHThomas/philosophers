/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:50:04 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/23 12:21:54 by bthomas          ###   ########.fr       */
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
	long			currtime;

	gettimeofday(&now, NULL);
	currtime = get_milisecs(&now);
	return (currtime - data->start_time);
}

int	all_finished(t_data *data)
{
	unsigned int	i;

	if (!data->num_eats_each)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		if (data->num_eaten[i] != data->num_eats_each)
			return (0);
		i++;
	}
	return (1);
}
