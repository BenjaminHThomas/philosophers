/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:17:50 by bento             #+#    #+#             */
/*   Updated: 2024/07/01 10:36:20 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

int	ft_errmsg(const char *s)
{
	write(2, s, ft_strlen(s));
	return (0);
}

void	print_state(t_philo *philo, char *status, char *colour)
{
	if (!is_stopped(philo->table))
		printf("%s %ld %d %s\n", colour, get_timestamp(philo->table),
			philo->idx + 1, status);
}
