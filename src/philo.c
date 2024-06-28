/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:43:57 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/28 10:31:51 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "thinking");
	philo_wait(philo->table, 1);
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = HUNGRY;
	pthread_mutex_unlock(&philo->self_mutex);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->idx % 2 == 0)
		usleep(10);
	lock_forks(philo);
	if (is_dead(philo))
	{
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = EATING;
	philo->last_ate = get_timestamp(philo->table);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "eating");
	philo_wait(philo->table, philo->table->time_to_eat);
	unlock_forks(philo);
}

static void	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->self_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->self_mutex);
	print_state(philo, "sleeping");
	philo_wait(philo->table, philo->table->time_to_sleep);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philo == 1)
	{
		print_state(philo, "thinking");
		philo_wait(philo->table, philo->table->time_to_die);
		is_dead(philo);
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
