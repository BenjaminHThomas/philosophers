/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:42:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/19 14:42:13 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_add_philo(t_philo **head, t_philo *new)
{
	t_philo	*p_philo;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	p_philo = *head;
	while (p_philo->next)
		p_philo = p_philo->next;
	p_philo->next = new;
}
