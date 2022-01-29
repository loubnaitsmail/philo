
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <pthread.h>
#include <sys/time.h>

typedef enum s_status
{
    alive,
    dead
}              t_status;

typedef struct s_data
{
    int             philo_nbr;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             repeat;
    long long       launch_time;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
    t_status        status;
    int             *list;
    
}               t_data;

typedef struct s_philo
{
    int id;
    t_data  *data;
    long long   last_meal;
    int         num_eaten;
}               t_philo;


t_data          *parse_data(int argc, char **argv);
long long       get_time_ms();
pthread_mutex_t *init_fork(t_data *data);
t_philo         *init_philos(t_data *data);
int             create_threads(t_philo *philo);

void            *is_dead(void *philo_i);
void            *routine(void *philo_i);


#endif