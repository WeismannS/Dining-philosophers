
#include "philo.h"


void ft_sleep(unsigned int ms)
{
    struct timeval start, current;
    gettimeofday(&start, NULL);
    gettimeofday(&current, NULL);
    while((current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000 < ms)
    	gettimeofday(&current, NULL);

}

void ft_free(t_philo **philos)
{
  int i;

  i = 0;
  while (philos[i])
  {

        free(philos[i]->meal_lock);
        free(philos[i]);

        i++;
  }
  free(philos);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

pthread_mutex_t ** set_forks(int *parsed_args)
{
  pthread_mutex_t **forks;
  int             i;

  i = 0;
  forks = (pthread_mutex_t ** ) malloc(sizeof(pthread_mutex_t *) * (parsed_args[0] + 1));
  forks[parsed_args[0]] = NULL;
  while(i < parsed_args[0])
  {
    forks[i] = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(forks[i++], NULL);
  }
  return (forks);
}


int * parse(char *av[], t_philo **philos, int ac)
{
  int *arr;
  unsigned long num;
  int i;

  i = 1;
  arr = malloc(sizeof(int) * (ac - 1) );
  while (av[i])
  {
    if (av[i][0] != '\0' && ft_atoi(av[i], &num))
      arr[i - 1] = num; 
    else
      return (free(arr),NULL);
    i++;
  }
  return (arr);
}