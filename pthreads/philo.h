/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:42 by baarif            #+#    #+#             */
/*   Updated: 2024/08/01 02:33:43 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*main_fork;
	pthread_mutex_t	*sec_fork;
	atomic_llong	last_meal_time;
	atomic_int		meals_eaten;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	atomic_int		num_philos;
	atomic_int		time_to_die;
	atomic_int		time_to_eat;
	atomic_int		time_to_sleep;
	atomic_int		num_meals;
	atomic_int		philos_finished_eaten;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	atomic_int		simulation_stop;
}					t_data;

int					parse_arguments(int argc, char **argv, t_data *data);
int					initialize_data(t_data *data);
void				start_simulation(t_data *data);
void				cleanup(t_data *data);
long long			get_time(void);
void				print_state(t_philo *philo, char *message);
int					ft_atoi(const char *str);
#endif
