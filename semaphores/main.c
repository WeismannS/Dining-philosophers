/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:34 by baarif            #+#    #+#             */
/*   Updated: 2024/08/11 20:57:11 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

int	initialize_data(t_data *data)
{
	int	i;

	i = 0;
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("death");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->num_philos);
	data->write = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	data->death = sem_open("death", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == SEM_FAILED || data->write == SEM_FAILED
		|| data->death == SEM_FAILED)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->simulation_stop = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	static int	i = 0;

	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("death");
	sem_close(data->write);
	sem_close(data->death);
	sem_close(data->forks);
	while (i < data->num_philos)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
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
	start_simulation(&data);
	sem_wait(data.death);
	cleanup(&data);
	return (0);
}
