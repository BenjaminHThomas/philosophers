/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:32 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/18 16:32:43 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_too_big(const char *s)
{
	int			i;
	unsigned	res;

	i = 0;
	res = 0;
	while (s && (s[i] == 32 || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s && s[i] == '+')
		i++;
	while (s && (s[i] >= '0' && s[i] <= '9'))
	{
		if (res > MAXUINT/10)
			return (1);
		res *= 10;
		res += s[i] - '0';
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

int	valid_input(int	ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (non_num(av[i]))
			return (0);
		i++;
	}
	return (1);
}
