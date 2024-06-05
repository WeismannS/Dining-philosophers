#include "philo.h"


int change_state(t_philo *philo, t_state state)
{
    pthread_mutex_lock(philo->state_change);
    *philo->s_tate = state;
    pthread_mutex_unlock(philo->state_change);
}

t_state read_state(t_philo *philo)
{
    t_state state;
    pthread_mutex_lock(philo->state_change);
    state = *philo->s_tate;
    pthread_mutex_unlock(philo->state_change);
    return (state);
}

