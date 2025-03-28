/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/01 10:36:12 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	if (philo->table->must_stop)
		return ;
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "is thinking", PINK);
	philo_wait(philo->table, 1);
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = HUNGRY;
	pthread_mutex_unlock(&philo->self_mutex);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->idx % 2 == 0)
		usleep(philo->table->time_to_eat / 2);
	lock_forks(philo);
	if (philo->table->must_stop)
	{
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = EATING;
	philo->last_ate = get_timestamp(philo->table);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "is eating", GREEN);
	philo_wait(philo->table, philo->table->time_to_eat);
	unlock_forks(philo);
}

static void	philo_sleep(t_philo *philo)
{
	if (philo->table->must_stop)
		return ;
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "is sleeping", YELLOW);
	philo_wait(philo->table, philo->table->time_to_sleep);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
	{
		print_state(philo, "is thinking", PINK);
		philo_wait(philo->table, philo->table->time_to_die + 10);
	}
	philo->left_fork = philo->idx;
	philo->right_fork = (philo->idx + 1) % philo->table->num_philo;
	while (!philo->table->must_stop)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		if (is_finished(philo->table, philo->idx))
			break ;
	}
	return (NULL);
}
