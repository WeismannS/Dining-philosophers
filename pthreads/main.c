/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:34 by baarif            #+#    #+#             */
/*   Updated: 2024/08/10 10:48:38 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->philos_finished_eaten = 0;
	if (!data->forks || !data->philos)
		return (0);
	pthread_mutex_init(&data->write_lock, NULL);
	data->simulation_stop = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i + 1;
		data->philos[i].main_fork = &data->forks[i];
		data->philos[i].sec_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

void	configure_hand(t_data *data)
{
	t_philo			*philos;
	static int		i = 0;
	pthread_mutex_t	*tmp;

	philos = data->philos;
	while (i < data->num_philos)
	{
		if (philos[i].id % 2 != 0)
		{
			tmp = philos[i].sec_fork;
			philos[i].sec_fork = philos[i].main_fork;
			philos[i].main_fork = tmp;
		}
		i++;
	}
	i = 0;
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_arguments(argc, argv, &data))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (!initialize_data(&data))
	{
		printf("Initialization failed\n");
		return (1);
	}
	if (data.num_philos == 1)
		return (0);
	configure_hand(&data);
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
