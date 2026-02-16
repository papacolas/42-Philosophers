/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:57:45 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/23 19:31:35 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!parse_and_init(&data, argc, argv))
		return (1);
	if (!simulation_begin(&data))
	{
		clean_total(&data);
		return (1);
	}
	wait_end_of_simulation(&data);
	usleep(100000);
	i = 0;
	while (i < data.args.nbr_philo)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philo[i].last_meal_philo);
		pthread_mutex_destroy(&data.philo[i].nbr_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.dead_mutex);
	free(data.forks);
	free(data.philo);
	return (0);
}
