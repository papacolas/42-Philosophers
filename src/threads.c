/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:15:24 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/23 19:33:24 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threading_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				routine, &data->philo[i]) != 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	threads_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (1);
}

int	simulation_begin(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL, monitor, data) != 0)
	{
		printf("Error : lors de la creation du thread monitor\n");
		return (0);
	}
	usleep(1000);
	if (!threading_philos(data))
		return (0);
	return (1);
}
