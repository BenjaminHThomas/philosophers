/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:57:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 13:00:56 by bthomas          ###   ########.fr       */
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
	t_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	if (!valid_input(ac, av))
		return (1);
	if (init(ac, av, &data))
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
