/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:17:50 by bento             #+#    #+#             */
/*   Updated: 2024/06/26 20:00:47 by bento            ###   ########.fr       */
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

void	print_state(t_philo *philo, char *status)
{
	printf("%ld %d is %s\n", get_timestamp(philo->table), philo->idx + 1, status);
}
