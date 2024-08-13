/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:45 by baarif            #+#    #+#             */
/*   Updated: 2024/08/13 00:28:06 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->main_fork);
	print_state(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_unlock(philo->main_fork);
		usleep((philo->data->time_to_die + 2) * 1000);
		return ;
	}
	pthread_mutex_lock(philo->sec_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	philo->last_meal_time = get_time();
	precise_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->main_fork);
	pthread_mutex_unlock(philo->sec_fork);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->simulation_stop)
	{
		philo_eat(philo);
		if (philo->data->num_meals != -1
			&& philo->meals_eaten == philo->data->num_meals)
		{
			((void)philo->data->philos_finished_eaten++);
			break ;
		}
		if (philo->data->simulation_stop)
			break ;
		print_state(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep);
		if (philo->data->simulation_stop)
			break ;
		print_state(philo, "is thinking");
		precise_sleep(1);
	}
	return (NULL);
}

void	check_philos(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	while (i < data->num_philos && !data->simulation_stop)
	{
		current_time = get_time();
		if (current_time - data->philos[i].last_meal_time > data->time_to_die)
		{
			print_state(&data->philos[i], "died");
			data->simulation_stop = 1;
			return ;
		}
		if (data->num_meals != -1
			&& data->philos_finished_eaten == data->num_philos)
		{
			print_state(&data->philos[i], "has eaten");
			data->simulation_stop = 1;
			return ;
		}
		i++;
	}
}

void	start_simulation(t_data *data)
{
	static int	i = 0;

	data->start_time = get_time();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philosopher,
				&data->philos[i]) != 0)
			return (printf("Failed to create thread\n"), (void)0);
		usleep(100);
		i++;
	}
	while (!data->simulation_stop)
	{
		check_philos(data);
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
