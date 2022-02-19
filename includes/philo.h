
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

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
    int             num_eat;
    long long       launch_time;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
    t_status        status;
    int             *list_id;
    
}               t_data;

typedef struct s_philo
{
    int id;
    t_data  *data;
    long long   last_meal;
    int         num_eaten;
}               t_philo;

//LIB FUNCTIONS
int	ft_atoi(const char *str);

//MAIN
int check_arg(int argc, char **argv);
t_philo *init_philos(t_data *data);
int create_threads(t_philo *philo);

//INIT 
t_data *parse_data(int argc, char **argv);
int *init_list(t_data *data);
void    update_list_id(t_data *data, int philo_id);
pthread_mutex_t *init_fork(t_data *data);

//STATUS
long long   get_time_ms(void);
void    print_dead(t_philo *philo);
void    print_status(t_philo *philo, char *str);
t_status    check_status(t_philo    *philo);

//ROUTINE
void    *is_dead(void *philo_i);
void    smart_sleep(long long time_eat, t_philo *philo);
void    serve_fork(t_philo *philo);
void    eating(t_philo *philo);
void    *routine(void *philo_i);
int	go_sleep(useconds_t usec);


#endif