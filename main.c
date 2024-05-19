#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>

t_philo *thread_init(t_dates dates,unsigned int *forks)
{
  t_philo *philo;
  
  philo = (t_philo *) malloc(sizeof(t_philo));
  philo->s_tate = NONE;
  philo->dates.time_to_die = dates.time_to_die;
  philo->dates.time_to_sleep = dates.time_to_sleep;
  philo->dates.time_to_eat = dates.time_to_eat;
  philo->dates.main_thread_birth = dates.main_thread_birth;
  philo->forks = forks;
  return (philo);
}

void *routine(void *arg)
{
  t_philo **philos;

  philos = (t_philo **) arg;
  
  return (NULL);
}

t_philo **init_philo(int *ac, unsigned int *forks)
{
  t_philo **philos;
  static int     i = 0;
  t_dates dates;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  dates.time_to_die = ac[1];
  dates.time_to_eat = ac[2];
  dates.time_to_sleep = ac[3];
  dates.main_thread_birth = tv.tv_usec;
  philos = malloc(sizeof(t_philo *) * (ac[0] +1 ));
  philos[ac[0]] = NULL;
  while (philos[i])
  {
    philos[i] = thread_init(dates,forks);
    pthread_create(&philos[i]->thread_id, NULL, routine, philos[i]);
    i++;
  } 
  i = 0;
  while(philos[i])
    pthread_join(philos[i++]->thread_id, NULL);
  return (philos);
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
int main(int ac, char *av[])
{
  t_philo **philos;
  unsigned int     forks;
  int *parsed_args;

  int  i = 0;  
  if (ac != 5 && ac != 6)
      exit(1);
  parsed_args = parse(av, philos, ac);
  if (!parsed_args)
    (free(parsed_args),printf("Failed"), exit(1));
  philos = init_philo(parsed_args, &forks);
  ft_free(philos);
  free(parsed_args);
}
