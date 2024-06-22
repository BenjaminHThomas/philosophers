/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:57:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/22 12:38:18 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Args:
 *   num_phils, time_to_die, time_to_eat, time_to_sleep
 *
 * Optional Arg:
 *   num_times_each_must_eat
 */

/*
	* example:
	*    3, 4, 1, 1
	*
*/
int	main(int ac, char **av)
{
	t_data			data;
	unsigned int	i;

	if (ac < 5 || ac > 6)
		return (1);
	if (!valid_input(ac, av))
		return (1);
	if (init(ac, av, &data))
	{
		cleanup(&data);
		return (1);
	}
	i = -1;
	while (++i < data.num_philo)
		pthread_join(data.threads[i], NULL);
	pthread_join(data.waiter, NULL);
	cleanup(&data);
	return (0);
}
