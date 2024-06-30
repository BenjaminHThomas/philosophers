/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hangman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:57:14 by bento             #+#    #+#             */
/*   Updated: 2024/06/30 09:16:29 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hangman(void *arg)
{
	t_table			*data;
	unsigned int	i;

	data = (t_table *)arg;
	while (!data->must_stop)
	{
		i = 0;
		while (i < data->num_philo)
		{
			is_dead(&data->philos[i]);
			i++;
		}
		usleep(100);
		if (all_finished(data))
			break ;
	}
	return (NULL);
}
