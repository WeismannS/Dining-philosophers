
#include "philo.h"
void ft_sleep(unsigned int microseconds)
{
    struct timeval start, current;
    gettimeofday(&start, NULL);
    gettimeofday(&current, NULL);
    while((current.tv_sec - start.tv_sec) * 1000000 + (current.tv_usec - start.tv_usec) < microseconds)
    	gettimeofday(&current, NULL);

}

void ft_free(t_philo **philos)
{
  int i;

  i = 0;
  while (philos[i])
    free(philos[i++]);
  free(philos);
}
