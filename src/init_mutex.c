/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:18:16 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/19 21:06:57 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_print_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (0);
	data->flag_print_mutex = 1;
	return (1);
}

int	ft_init_dead_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		data->flag_print_mutex = 0;
		return (0);
	}
	data->flag_dead_mutex = 1;
	return (1);
}

int	ft_init_forks_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->print);
			pthread_mutex_destroy(&data->dead_mutex);
			data->flag_forks_mutex = 0;
			data->flag_dead_mutex = 0;
			data->flag_print_mutex = 0;
			return (0);
		}
		i++;
	}
	data->flag_forks_mutex = 1;
	return (1);
}

int	ft_init_philo_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		if (pthread_mutex_init(&data->philo[i].last_meal_philo, NULL) != 0)
		{
			clean_total(data);
			return (0);
		}
		data->flag_nbr_last_meal_philo_mutex = 1;
		if (pthread_mutex_init(&data->philo[i].nbr_eaten_mutex, NULL) != 0)
		{
			clean_total(data);
			return (0);
		}
		data->flag_nbr_eaten_mutex = 1;
		i++;
	}
	return (1);
}
