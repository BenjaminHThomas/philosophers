/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:02:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:15:22 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_table *data, int left_fork, int right_fork, int idx)
{

}

void	unlock_forks(t_table *data, int left_fork, int right_fork)
{

}

int	is_dead(t_table *data, int idx)
{
	long	curr_time;

	curr_time = get_timestamp(data);
	if (curr_time - data->philos[idx].last_ate >= data->time_to_die)
	{
		if (!data->must_stop)
		{
			printf("%ld %d is dead\n", curr_time, idx + 1);
			data->must_stop = 1;
		}
		return (1);
	}
	return (0);
}
