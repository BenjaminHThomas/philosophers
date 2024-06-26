/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:32 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/26 19:17:18 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_too_big(const char *s)
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
		if (res >= INT_MAX / 10)
			return (1);
		i++;
	}
	return (0);
}

int	non_num(const char *s)
{
	while (*s)
	{
		if (*s > '9' || *s < '0')
			return (1);
		s++;
	}
	return (0);
}

int	valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ft_utoi(av[1]) > 200)
		return (0);
	while (i < ac)
	{
		if (non_num(av[i]))
			return (0);
		if (num_too_big(av[i]))
			return (0);
		i++;
	}
	return (1);
}
