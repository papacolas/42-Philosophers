/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:55:47 by ncrivell          #+#    #+#             */
/*   Updated: 2025/05/23 19:42:19 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_args
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_lunching;
}	t_args;

typedef struct s_philo
{
	int					id;
	int					nbr_eaten;
	unsigned long long	last_meal;
	pthread_t			thread;
	pthread_mutex_t		nbr_eaten_mutex;
	pthread_mutex_t		last_meal_philo;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	int					flag_is_dead;
	int					flag_enought_meal;
	t_args				args;
	t_philo				*philo;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	pthread_t			monitor_thread;
	int					flag_dead_mutex;
	int					flag_print_mutex;
	int					flag_forks_mutex;
	int					flag_nbr_eaten_mutex;
	int					flag_nbr_last_meal_philo_mutex;
	unsigned long long	start_time;
}	t_data;

//--------- main.c ---------//

//--------- parsing.c ---------//
bool				ft_is_numeric(char *str);
bool				validate_arguments(int argc, char **argv, t_data *data);
bool				ft_extract_infos(t_data *data, int argc, char **argv);
int					parse_and_init(t_data *data, int argc, char **argv);
//--------- struct.c ---------//
void				*routine(void *id);

//--------- utils.c ---------//
int					ft_atoi(const char *nptr);
void				ft_fail(char *msg);
void				ft_putstr_fd(char *s, int fd);
bool				is_dead(t_philo *philo);
void				ft_usleep(unsigned long long time_ms, t_philo *philo);
//--------- init.c ---------//
int					init_struct_philos(t_data *data);
int					init_structs_and_mutex(t_data *data);
int					init_mutex(t_data *data);
int					init_struct_data(t_data *data);
//--------- init_mutex ------//
int					ft_init_print_mutex(t_data *data);
int					ft_init_dead_mutex(t_data *data);
int					ft_init_forks_mutex(t_data *data);
int					ft_init_philo_mutex(t_data *data);
//--------- time.c ---------//
unsigned long long	get_actual_time(void);
unsigned long long	timestamp(t_philo *philo);
void				init_time(t_data *data);

//--------- threads.c ---------//
int					threads_join(t_data *data);
int					threading_philos(t_data *data);
int					simulation_begin(t_data *data);
//--------- routine.c ---------//
int					take_forks(t_philo *philo, pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);
int					eating(t_philo *philo, pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);
int					sleeping_and_thinking(t_philo *philo);
void				init_forks(t_philo *philo, pthread_mutex_t **fork1,
						pthread_mutex_t **fork2);
void				*monitor(void *arg);
//--------- routine_sub_functions ------//
int					single_philo(t_philo *philo);
int					take_all_forks(t_philo *philo, pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);
void				ft_init_philo(t_philo *philo, pthread_mutex_t **fork1,
						pthread_mutex_t **fork2);
void				unlock_forks(pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);
//--------- monitor.c ---------//
void				*monitor(void *arg);
void				wait_end_of_simulation(t_data *data);
//--------- monito_check -------//
int					should_exit(t_data *data);
int					philo_death(t_data *data);
int					all_meals(t_data *data);
void				end_simulation_all_ate(t_data *data);

//--------- cleaning.c ---------//
void				clean_philos_mutex(t_data *data);
void				clean_forks_mutex(t_data *data);
void				clean_others_mutex(t_data *data);
void				free_memory(t_data *data);
void				clean_total(t_data *data);
#endif
