/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monito_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:56:48 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/26 15:05:55 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_exit(t_data *data)
{
	int	should_exit;

	pthread_mutex_lock(&data->dead_mutex);
	should_exit = data->flag_is_dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (should_exit);
}

int	philo_death(t_data *data)
{
	int	i;
	int	time_between_meal;

	i = 0;
	while (i < data->args.nbr_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_philo);
		time_between_meal = get_actual_time() - data->philo[i].last_meal;
		if (time_between_meal > data->args.time_to_die)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->flag_is_dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			usleep(1000);
			pthread_mutex_lock(&data->print);
			printf("%llu %d %s died %s\n", timestamp(&data->philo[i]),
				data->philo[i].id, RED, RESET);
			pthread_mutex_unlock(&data->print);
			pthread_mutex_unlock(&data->philo[i].last_meal_philo);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_philo);
		i++;
	}
	return (0);
}

void	end_simulation_all_ate(t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%llu Tous les philosophes ont mange %d fois\n",
		timestamp(&data->philo[0]), data->args.nbr_lunching);
	pthread_mutex_lock(&data->dead_mutex);
	data->flag_is_dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->print);
}

int	all_meals(t_data *data)
{
	int	i;
	int	enougth_meal;

	if (data->args.nbr_lunching <= 0)
		return (0);
	enougth_meal = 0;
	i = 0;
	while (i < data->args.nbr_philo)
	{
		pthread_mutex_lock(&data->philo[i].nbr_eaten_mutex);
		if (data->args.nbr_lunching > 0
			&& data->philo[i].nbr_eaten >= data->args.nbr_lunching)
			enougth_meal++;
		pthread_mutex_unlock(&data->philo[i].nbr_eaten_mutex);
		i++;
	}
	if (enougth_meal == data->args.nbr_philo)
	{
		end_simulation_all_ate(data);
		return (1);
	}
	return (0);
}
