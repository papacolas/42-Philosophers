/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:48:08 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/19 21:03:27 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struct_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->args.nbr_philo);
	if (!data->philo)
	{
		ft_fail("Malloc Error\n");
		return (0);
	}
	while (i < data->args.nbr_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].nbr_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork
			= &data->forks[(i + 1) % data->args.nbr_philo];
		i++;
	}
	return (1);
}

int	init_struct_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args.nbr_philo);
	if (!data->forks)
	{
		ft_fail("Malloc Error\n");
		return (0);
	}
	data->flag_is_dead = 0;
	data->flag_enought_meal = 0;
	data->flag_dead_mutex = 0;
	data->flag_print_mutex = 0;
	data->flag_forks_mutex = 0;
	data->flag_nbr_eaten_mutex = 0;
	data->flag_nbr_last_meal_philo_mutex = 0;
	return (1);
}

/**
 * Initialise les mutex suivants :
 * Mutex d'affichage (print)
 * Mutex pour le drapeau de mort (dead_mutex)
 * Mutex pour les fourchettes (forks[])
 * Mutex pour chaque philosophe (last_meal_philo et nbr_eaten_mutex)
 */

int	init_mutex(t_data *data)
{
	if (!ft_init_print_mutex(data))
		return (0);
	if (!ft_init_dead_mutex(data))
		return (0);
	if (!ft_init_forks_mutex(data))
		return (0);
	if (!ft_init_philo_mutex(data))
		return (0);
	return (1);
}

int	init_structs_and_mutex(t_data *data)
{
	if (!init_struct_data(data))
		return (0);
	if (!init_struct_philos(data))
		return (0);
	if (!init_mutex(data))
	{
		free(data->philo);
		free(data->forks);
		return (0);
	}
	return (1);
}
