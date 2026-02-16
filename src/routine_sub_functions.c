/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sub_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:26:36 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/28 21:32:31 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NE PAS essayer de prendre une deuxième fourchette
// Attendre jusqu'à la mort du philosophe
int	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s has taken a fork %s\n",
		timestamp(philo), philo->id, CYAN, RESET);
	pthread_mutex_unlock(&philo->data->print);
	while (!is_dead(philo))
		usleep(1000);
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (0);
}
/**
 * Prend la seconde fourchette pour un philosophe.
 *
 * @param philo Pointeur vers le philosophe
 * @param fork1 Première fourchette (déjà prise)
 * @param fork2 Seconde fourchette à prendre
 * @return 1 si la fourchette a été prise, 0 sinon
 */

int	take_all_forks(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s has taken a fork %s\n",
		timestamp(philo), philo->id, YELLOW, RESET);
	pthread_mutex_unlock(&philo->data->print);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(fork1);
		return (0);
	}
	pthread_mutex_lock(fork2);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s has taken a fork %s\n",
		timestamp(philo), philo->id, YELLOW, RESET);
	pthread_mutex_unlock(&philo->data->print);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		return (0);
	}
	return (1);
}

void	ft_init_philo(t_philo *philo, pthread_mutex_t **fork1,
		pthread_mutex_t **fork2)
{
	pthread_mutex_lock(&philo->last_meal_philo);
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->last_meal_philo);
	init_forks(philo, fork1, fork2);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->args.time_to_eat / 2, philo);
}

void	unlock_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}
