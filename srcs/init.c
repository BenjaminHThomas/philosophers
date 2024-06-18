/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:14:58 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/18 16:22:37 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(int idx)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->idx = idx;
	philo->fork = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	philo->next = NULL;
	return (philo);
}

int	init(int ac, char **av, t_data *data)
{
	long	temp;

	memset(data, 0, sizeof(data));
	data->head = new_philo(0);
	if (!data->head)
		return (1);
	return (0);
}
