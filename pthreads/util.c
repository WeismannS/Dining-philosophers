/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baarif <baarif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:33:49 by baarif            #+#    #+#             */
/*   Updated: 2024/08/01 02:33:50 by baarif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *message)
{
	long long	current_time;

	current_time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->simulation_stop && message[4] != 'e')
		printf("%lld %d %s \n", current_time, philo->id, message);
	if (!philo->data->simulation_stop && message[4] == 'e')
		printf("%lld all philos %s %d meals\n", current_time, message,
			philo->meals_eaten);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (0);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->num_meals <= 0))
		return (0);
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}
