/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:45 by baarif            #+#    #+#             */
/*   Updated: 2024/08/11 15:03:47 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->num_meals)
	{
		philo->data->simulation_stop = 1;
		sem_post(philo->data->death);
		return ;
	}
	sem_wait(philo->data->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_eaten++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->simulation_stop)
	{
		philo_eat(philo);
		if (philo->data->simulation_stop)
			break ;
		print_state(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->simulation_stop)
			break ;
		print_state(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}

void	check_philos(t_philo *philo)
{
	long long	current_time;

	while (!philo->data->simulation_stop)
	{
		current_time = get_time();
		if (current_time - philo->last_meal_time > philo->data->time_to_die)
		{
			philo->data->simulation_stop = 1;
			sem_wait(philo->data->write);
			printf("%lld %d died\n", current_time - philo->data->start_time,
				philo->id + 1);
			sem_post(philo->data->death);
			break ;
		}
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			if (pthread_create(&data->philos[i].thread, NULL, philosopher,
					&data->philos[i]) != 0)
			return (printf("Failed to create thread\n"), (void) 0);
		}
		usleep(100);
		i++;
	}
	if (i == data->num_philos)
		return ;
	while (!data->simulation_stop)
	{
		check_philos(&data->philos[i]);
		usleep(1000);
	}
	pthread_join(data->philos[i].thread, NULL);
}
