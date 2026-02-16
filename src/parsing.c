/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:01:22 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/23 19:33:11 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	while (str[i] >= 48 && str[i] <= 57)
	{
		i++;
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

bool	ft_extract_infos(t_data *data, int argc, char **argv)
{
	data->args.nbr_philo = ft_atoi(argv[1]);
	data->args.time_to_die = ft_atoi(argv[2]);
	data->args.time_to_eat = ft_atoi(argv[3]);
	data->args.time_to_sleep = ft_atoi(argv[4]);
	data->args.nbr_lunching = -1;
	if (argc == 6)
	{
		data->args.nbr_lunching = ft_atoi(argv[5]);
		if (data->args.nbr_lunching <= 0 || data->args.nbr_lunching > INT_MAX)
			return (false);
	}
	if (data->args.nbr_philo <= 0
		|| data->args.time_to_die <= 0
		|| data->args.time_to_eat <= 0
		|| data->args.time_to_sleep <= 0
		|| data->args.nbr_philo > INT_MAX
		|| data->args.time_to_die > INT_MAX
		|| data->args.time_to_eat > INT_MAX
		|| data->args.time_to_sleep > INT_MAX)
		return (false);
	return (true);
}

bool	validate_arguments(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_fail("Pas le bon nombre d'arguments\n");
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_is_numeric(argv[i]))
		{
			ft_fail("Caracteres autres que numeriques");
			return (false);
		}
		i++;
	}
	if (!ft_extract_infos(data, argc, argv))
		return (false);
	return (true);
}

int	parse_and_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	memset(data, 0, sizeof(t_data));
	data->flag_is_dead = 0;
	data->flag_enought_meal = 0;
	if (!validate_arguments(argc, argv, data))
		return (0);
	if (!init_structs_and_mutex(data))
	{
		return (0);
	}
	init_time(data);
	while (i < data->args.nbr_philo)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_philo);
		data->philo[i].last_meal = get_actual_time();
		pthread_mutex_unlock(&data->philo[i].last_meal_philo);
		i++;
	}
	return (1);
}
