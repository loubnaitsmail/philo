#include "philo.h"

///////////////////// GET TIME ///////////////////
long long   get_time_ms(void)
{
    //printf("GET TIME\n");
    struct timeval  tv;
    long long       time_ms;

    gettimeofday(&tv, NULL);
    time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    //printf("launch time ms = %lld\n", launch_time_ms);
    return(time_ms);
}

//////////////////// CHECK STATUT /////////////////////////////////
t_status    check_status(t_philo    *philo)
{
    //printf("CHECK STATUS\n");
    long long   time_ms;

    time_ms = get_time_ms();
    if (philo->last_meal == 0)
        philo->last_meal = get_time_ms() - 1;
    //printf("last meal was 0 -> %lld\n", philo->last_meal);

    if (philo->data->status == dead)
    {
        //printf("Status was DEAD\n");
        return (dead);
    }
    if (time_ms - philo->last_meal > philo->data->time_die)
    {
        print_dead(philo);
        //printf("Status is now DEAD\n");
        return (dead);
    }
    //printf("Status is still ALIVE\n");
    return (alive);
}

/////////////////  PRINT DEAD  ////////////////////////////////////
void    print_dead(t_philo *philo)
{
    long long   time_ms;
    //printf("Lock to print dead\n");
    pthread_mutex_lock(&philo->data->print);
    time_ms = get_time_ms() - philo->data->launch_time;
    if (philo->data->status == alive)
    {
        philo->data->status = dead;
        //printf("will sleep\n");
        usleep(1000);
        printf("\033[1;92m%lldms : Philo %d\033[0;39m \033[1;91mdied 💀 \033[0;39m", time_ms, philo->id);
    }
    //printf("Unlock after print dead\n");
    pthread_mutex_unlock(&philo->data->print);
}

//////////////////// PRINT STATUT /////////////////////////////////
void    print_status(t_philo *philo, char *str)
{
    //printf("PRINT STATUS\n";)
    long long   time_ms;

    //printf("Lock to print status, id = %d\n", philo->id);
    pthread_mutex_lock(&philo->data->print);
    time_ms = get_time_ms() - philo->data->launch_time;

    if (philo->data->status == alive)
        printf("\033[1;92m%lldms : Philo %d\033[0;39m %s\n", time_ms, philo->id, str);
    
    //printf("Unlock after print status\n");
    pthread_mutex_unlock(&philo->data->print);
}