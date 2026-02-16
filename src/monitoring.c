/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:22:53 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/23 19:32:40 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(500);
	while (1)
	{
		if (should_exit(data))
		{
			break ;
		}
		if (philo_death(data))
		{
			return (NULL);
		}
		if (all_meals(data))
		{
			return (NULL);
		}
		usleep(5000);
	}
	pthread_mutex_lock(&data->dead_mutex);
	data->flag_is_dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	return (NULL);
}

void	wait_end_of_simulation(t_data *data)
{
	int	j;

	pthread_join(data->monitor_thread, NULL);
	pthread_mutex_lock(&data->dead_mutex);
	data->flag_is_dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	usleep(5000);
	j = 0;
	while (j < data->args.nbr_philo)
	{
		pthread_join(data->philo[j].thread, NULL);
		j++;
	}
}
