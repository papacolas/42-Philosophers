/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:13:55 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/19 21:01:25 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (is_dead(philo))
		return (0);
	if (philo->data->args.nbr_philo == 1)
		return (single_philo(philo));
	return (take_all_forks(philo, fork1, fork2));
}

int	eating(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (is_dead(philo))
	{
		unlock_forks(fork1, fork2);
		return (0);
	}
	pthread_mutex_lock(&philo->last_meal_philo);
	philo->last_meal = get_actual_time();
	pthread_mutex_unlock(&philo->last_meal_philo);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s is eating %s\n", timestamp(philo),
		philo->id, GREEN, RESET);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->nbr_eaten_mutex);
	philo->nbr_eaten++;
	pthread_mutex_unlock(&philo->nbr_eaten_mutex);
	if (is_dead(philo))
	{
		unlock_forks(fork1, fork2);
		return (0);
	}
	ft_usleep(philo->data->args.time_to_eat, philo);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
	return (1);
}

int	sleeping_and_thinking(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s is sleeping %s\n", timestamp(philo),
		philo->id, BLUE, RESET);
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->args.time_to_sleep, philo);
	if (is_dead(philo))
		return (0);
	pthread_mutex_lock(&philo->data->print);
	printf("%llu %d %s is thinking %s\n", timestamp(philo),
		philo->id, CYAN, RESET);
	pthread_mutex_unlock(&philo->data->print);
	usleep(500);
	return (1);
}

void	init_forks(t_philo *philo, pthread_mutex_t **fork1,
	pthread_mutex_t **fork2)
{
	if (philo->id % 2 == 0)
	{
		*fork1 = philo->left_fork;
		*fork2 = philo->right_fork;
	}
	else
	{
		*fork1 = philo->right_fork;
		*fork2 = philo->left_fork;
	}
}
/**
 * Initialise le philosophe avant le début de sa routine.
 * Configure son premier repas et l'ordre des fourchettes.
 *
 * @param philo Pointeur vers le philosophe
 * @param fork1 Pointeur vers le pointeur de la première fourchette
 * @param fork2 Pointeur vers le pointeur de la seconde fourchette
 */

void	*routine(void *id)
{
	t_philo			*philo;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				nbr_meals_done;

	philo = (t_philo *)id;
	ft_init_philo(philo, &fork1, &fork2);
	while (!is_dead(philo))
	{
		if (!take_forks(philo, fork1, fork2))
			return (NULL);
		if (!eating(philo, fork1, fork2))
			return (NULL);
		pthread_mutex_lock(&philo->nbr_eaten_mutex);
		nbr_meals_done = philo->nbr_eaten;
		pthread_mutex_unlock(&philo->nbr_eaten_mutex);
		if (philo->data->args.nbr_lunching > 0
			&& nbr_meals_done >= philo->data->args.nbr_lunching)
			break ;
		if (!sleeping_and_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
