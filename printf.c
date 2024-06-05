#include "philo.h"

int ft_printf(t_philo *philo, t_state state, int fork) {
  pthread_mutex_lock(philo->print);
  static int flag = 0;
  if (flag == 1)
    ;
  else if (fork == 3) {
    flag = 1;
    (printf("%ld : %d is dead\n",
            get_current_time() - philo->dates.main_thread_birth, philo->id),
     1);
  } else if (state == EATING && fork == 1)
    (printf("%ld : %d has taken the main fork\n",
            get_current_time() - philo->dates.main_thread_birth, philo->id));
  else if (state == EATING && fork == 2)
    (printf("%ld : %d has taken the sec fork\n",
            get_current_time() - philo->dates.main_thread_birth, philo->id),
     printf("%ld : philo %d is eating\n",
            get_current_time() - philo->dates.main_thread_birth, philo->id));
  else if (state == SLEEPING)
    (printf("%ld : %d is sleeping\n",
            get_current_time() - philo->dates.main_thread_birth, philo->id));
  return pthread_mutex_unlock(philo->print);
}
