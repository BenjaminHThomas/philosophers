/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:50:04 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/20 18:34:07 by bthomas          ###   ########.fr       */
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
