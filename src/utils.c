/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:27:51 by ncrivell          #+#    #+#             */
/*   Updated: 2025/04/30 18:00:05 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	a;
	int	i;

	a = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		a = a * 10 + (nptr[i] - '0');
		i++;
	}
	return (a);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_fail(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
}

bool	is_dead(t_philo *philo)
{
	bool	died;
	int		flag;

	died = false;
	pthread_mutex_lock(&philo->data->dead_mutex);
	flag = philo->data->flag_is_dead;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (flag == 0)
		died = false;
	else
		died = true;
	return (died);
}

void	ft_usleep(unsigned long long time_ms, t_philo *philo)
{
	unsigned long long	start_time;
	unsigned long long	elapsed_time;

	start_time = get_actual_time();
	while (1)
	{
		if (is_dead(philo))
			return ;
		elapsed_time = get_actual_time() - start_time;
		if (elapsed_time >= time_ms)
			break ;
		usleep(100);
	}
}
