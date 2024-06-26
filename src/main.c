/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:57:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:23:27 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table			data;
	unsigned int	i;

	if (ac < 5 || ac > 6)
		return (ft_errmsg("Usage:./philo <num_phils> <time_to_die> "
				"<time_to_eat> <time_to_sleep> [num_times_each_must_eat]\n"));
	if (!valid_input(ac, av))
		return (ft_errmsg("Invalid input\n"));
	if (init(ac, av, &data))
	{
		cleanup(&data);
		return (ft_errmsg("Error initializing\n"));
	}
	i = -1;
	while (++i < data.num_philo)
		pthread_join(data.threads[i], NULL);
	cleanup(&data);
	return (0);
}
