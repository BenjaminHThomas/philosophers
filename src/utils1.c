/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:50:04 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:10:27 by bento            ###   ########.fr       */
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

int	is_finished(t_table *data, int idx)
{
	int	retval;

	if (data->eat_limit == -1)
		return (0);
	pthread_mutex_lock(&data->philos[idx].self_mutex);
	retval = (data->philos[idx].num_eaten == data->eat_limit);
	pthread_mutex_unlock(&data->philos[idx].self_mutex);
	return (retval);
}

int	all_finished(t_table *data)
{
	unsigned int	i;

	if (data->eat_limit == -1)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		if (!is_finished(data, i))
			return (0);
		i++;
	}
	return (1);
}
