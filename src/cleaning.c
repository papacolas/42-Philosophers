/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:45:13 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/21 12:33:22 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philos_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		if (data->flag_nbr_last_meal_philo_mutex)
			pthread_mutex_destroy(&data->philo[i].last_meal_philo);
		if (data->flag_nbr_eaten_mutex)
			pthread_mutex_destroy(&data->philo[i].nbr_eaten_mutex);
		i++;
	}
	data->flag_nbr_last_meal_philo_mutex = 0;
	data->flag_nbr_eaten_mutex = 0;
}

void	clean_forks_mutex(t_data *data)
{
	int	i;

	if (data->flag_forks_mutex)
	{
		i = 0;
		while (i < data->args.nbr_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		data->flag_forks_mutex = 0;
	}
}

void	clean_others_mutex(t_data *data)
{
	if (data->flag_dead_mutex)
	{
		pthread_mutex_destroy(&data->dead_mutex);
		data->flag_dead_mutex = 0;
	}
	if (data->flag_print_mutex)
	{
		pthread_mutex_destroy(&data->print);
		data->flag_print_mutex = 0;
	}
}

void	free_memory(t_data *data)
{
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
}

/**
 * clean_philo_mutex -> Nettoie les philos
 * clean_forks_mutex -> Nettoie les fourchettes
 * clean_others_mutex -> Nettoie les mutex globaux
 * free_memory -> Libere la memoire
 * a la fin on reinitialise les flags
 */

void	clean_total(t_data *data)
{
	if (!data)
		return ;
	clean_philos_mutex(data);
	clean_forks_mutex(data);
	clean_others_mutex(data);
	free_memory(data);
	data->flag_is_dead = 0;
	data->flag_enought_meal = 0;
	data->flag_print_mutex = 0;
	data->flag_nbr_eaten_mutex = 0;
	data->flag_nbr_last_meal_philo_mutex = 0;
}
