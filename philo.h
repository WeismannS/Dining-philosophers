#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
typedef enum State {
  NONE = 0, 
  EATING,
  SLEEPING,
  THINKIN,
} t_state;

typedef struct s_dates {
  
  unsigned char time_to_die;
  unsigned char time_to_eat;
  unsigned char time_to_sleep;
  unsigned long main_thread_birth;
} t_dates;

typedef struct s_philo {
  t_state       s_tate;
  unsigned long thread_id;
  unsigned int  *forks;
  t_dates       dates;
} t_philo;

void ft_sleep(unsigned int microseconds);
void ft_free(t_philo **philos);
int	ft_atoi(const char *s, unsigned long *num);


#endif
