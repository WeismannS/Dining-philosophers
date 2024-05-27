#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
typedef enum State {
  NONE = 0, 
  EATING,
  SLEEPING,
  THINKIN,
  DEAD
} t_state;

typedef struct s_dates {
  
  unsigned long time_to_die;
  unsigned long time_to_eat;
  unsigned long time_to_sleep;
  unsigned long main_thread_birth;
  unsigned long last_meal_date;
} t_dates;

typedef struct s_philo {
  volatile t_state       s_tate;
  unsigned long thread_id;
  unsigned char id;
  pthread_mutex_t *meal_lock;
  pthread_mutex_t *main_hand;
  pthread_mutex_t *sec_hand;
  pthread_mutex_t *state_change;
  pthread_mutex_t *self;
  t_dates       dates;
  size_t       meals_eaten;
} t_philo;

void ft_sleep(unsigned int microseconds);
void ft_free(t_philo **philos);
int	ft_atoi(const char *s, unsigned long *num);
void ft_printf(char *s, long j);
size_t	get_current_time(void);
pthread_mutex_t ** set_forks(int *parsed_args);
int * parse(char *av[], t_philo **philos, int ac);
t_state read_state(t_philo *philo);
int change_state(t_philo *philo, t_state state);
#endif
