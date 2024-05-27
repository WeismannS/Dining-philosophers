#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include <signal.h>
t_philo *thread_init(t_dates dates, int id, pthread_mutex_t *fork, int *ac)
{
  t_philo *philo;

  philo = (t_philo *)malloc(sizeof(t_philo));
  philo->s_tate = NONE;
  philo->dates.time_to_die = dates.time_to_die;
  philo->dates.time_to_sleep = dates.time_to_sleep;
  philo->dates.time_to_eat = dates.time_to_eat;
  philo->meals_eaten = 0;
  philo->meal_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  philo->state_change = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(philo->meal_lock, NULL);
  pthread_mutex_init(philo->state_change, NULL);
  philo->main_hand = fork;
  philo->id = (unsigned char)id;
  return (philo);
}

void eat(t_philo *philo)
{
  pthread_mutex_lock(philo->main_hand);
 
   printf("Checking if dead\n");
      printf("Checking if dead 2\n");
  printf("%ld :%d has taken the main fork\n", get_current_time() - philo->dates.main_thread_birth, philo->id);
  pthread_mutex_lock(philo->sec_hand);
 
  printf("%ld : %d has taken the sec fork\n", get_current_time() - philo->dates.main_thread_birth, philo->id);
  pthread_mutex_lock(philo->meal_lock);
  philo->dates.last_meal_date = get_current_time();
  pthread_mutex_unlock(philo->meal_lock);
  printf("%ld : philo %d is eating\n", get_current_time() - philo->dates.main_thread_birth, philo->id);
  ft_sleep(philo->dates.time_to_eat);
  printf("%ld stopped eating\n", get_current_time() - philo->dates.main_thread_birth);
  pthread_mutex_unlock(philo->main_hand);
  pthread_mutex_unlock(philo->sec_hand);

}

void *routine(void *arg)
{
  t_philo *philo;
  struct timeval tv;
  struct timeval tv2;

  philo = (t_philo *)arg;
  while (read_state(philo) != DEAD)
  {
    eat(philo);
    ft_sleep(philo->dates.time_to_sleep);
  }
  return (philo);
}
void set_hands(t_philo **philos, pthread_mutex_t **forks, int *ac)
{
  int i;

  i = 0;
  philos[0]->sec_hand = forks[ac[0] - 1];
  i++;
  while (philos[i])
  {
    if ((philos[i]->id % 2) == 0)
    {
      philos[i]->main_hand = forks[i - 1];
      philos[i]->sec_hand = forks[i];
    }
    else
    {
      philos[i]->main_hand = forks[i];
      philos[i]->sec_hand = forks[i - 1];
    }
    i++;
  }
}

t_philo **init_philo(int *ac, pthread_mutex_t **forks)
{
  t_philo **philos;
  static int i = 0;
  t_dates dates;
  unsigned long date;

  dates.time_to_die = ac[1];
  dates.time_to_eat = ac[2];
  dates.time_to_sleep = ac[3];
  philos = malloc(sizeof(t_philo *) * (ac[0] + 1));
  philos[ac[0]] = NULL;
  while (i < ac[0])
  {
    philos[i] = thread_init(dates, i + 1, forks[i], ac);
    i++;
  }
  set_hands(philos, forks, ac);
  i = 0;
  date = get_current_time();
  while (philos[i])
  {
    philos[i]->dates.main_thread_birth = date;
    philos[i]->dates.last_meal_date = date;
    pthread_create(&philos[i]->thread_id, NULL, routine, philos[i]);
    i++;
  }
  return (philos);
}

void clear_thread(t_philo **philos)
{
  int i = 0;
  while (philos[i])
  {
    pthread_detach(philos[i]->thread_id);
    pthread_cancel(philos[i]->thread_id);
    pthread_kill(philos[i]->thread_id, SIGINT);
    i++;
  }
}

void set_all_dead(t_philo **philos)
{
  int i;
  i = 0;
  while (philos[i])
  {
    change_state(philos[i], DEAD);
    i++;
  }
  i = 0;
 
}

int main(int ac, char *av[])
{
  t_philo **philos;
  pthread_mutex_t **forks;
  int *parsed_args;
  int i = 0;

  if (ac != 5 && ac != 6)
    exit(1);
  parsed_args = parse(av, philos, ac);
  if (!parsed_args)
    (free(parsed_args), printf("Failed"), exit(1));
  forks = set_forks(parsed_args);
  philos = init_philo(parsed_args, forks);
  int pepe = 1;
  while (pepe)
  {
    int j = 0;
    while (philos[j])
    {
      pthread_mutex_lock(philos[j]->meal_lock);
      if ((get_current_time() - philos[j]->dates.last_meal_date) > philos[j]->dates.time_to_die || philos[j]->meals_eaten >= parsed_args[4])
      {
        printf("-->%ld\n", philos[j]->dates.time_to_die);
        printf("%ld : %d has died!\n", get_current_time() - philos[j]->dates.last_meal_date, philos[j]->id);
        pthread_mutex_unlock(philos[j]->meal_lock);
        set_all_dead(philos);
        pepe = 0;
        break;
      }
      pthread_mutex_unlock(philos[j]->meal_lock);
      j++;
    }
  }
  ft_free(philos);
  ft_free((t_philo **)forks);
  free(parsed_args);
}
