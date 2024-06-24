/* Used to hold waiter that don't work properly, will delete later*/

void	*waiter(void *waiter_data)
{
	t_data	*data;
	int		hungriest;

	data = (t_data *)waiter_data;
	if (data->num_philo == 1)
		return (NULL);
	first_round_eat(data);
	while (!data->dead_philo && !all_finished(data))
	{
		hungriest = get_hungriest(data);
		if (hungriest != -1)
		{
			pthread_mutex_lock(&data->data_mutex);
			data->can_eat[hungriest] = 1;
			pthread_mutex_unlock(&data->data_mutex);
		}
		usleep(500);
	}
	return (NULL);
}

void	*waiter(void *waiter_data)
{
	t_data			*data;
	unsigned int	i;

	data = (t_data *)waiter_data;
	if (data->num_philo <= 1)
		return (NULL);
	while (!data->dead_philo && !all_finished(data))
	{
		i = 0;
		while (i < data->num_philo)
		{
			if (!data->is_sleeping[i] && !data->can_eat[i]
				&& !neighbours_can_eat(i, data)
				&& !is_finished(data, i))
			{
				pthread_mutex_lock(&data->data_mutex);
				data->can_eat[i] = 1;
				pthread_mutex_unlock(&data->data_mutex);
			}
			i++;
			usleep(50);
		}
		usleep(1000);
	}
	return (NULL);
}