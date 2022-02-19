#include "philo.h"

///////////////////// IS DEAD ///////////////////////////////////
void    *is_dead(void *philo_i)
{
    //printf("IS DEAD FUNC\n");
    t_philo *philo;

    philo = philo_i;
    while (1)
    {
        //printf("GO CHECK STATUS\n");
        check_status(philo);
    }
}

///////////////// SMART SLEEP ///////////////////////////////////////
void    smart_sleep(long long time_eat, t_philo *philo)
{
    long long   time_ms;
    time_ms = get_time_ms();
    //printf("SMART SLEEP, time_eat = %lld, time_ms = %lld\n", time_eat, time_ms);
    check_status(philo);
    while (philo->data->status == alive)
    {
        if (get_time_ms() - time_ms > philo->data->time_die - 1)
        {
            //printf("get_time_ms() - time_ms = %lld > philo->data->time_die - 1 = %d\n", get_time_ms() - time_ms, philo->data->time_die - 1);
            print_dead(philo);
        }
        if (get_time_ms() - time_ms >= time_eat)
        {
            //printf("Break, get_time_ms() - time_ms = %lld >= time_eat = %lld\n", get_time_ms() - time_ms, time_eat);
            break;
        }
        //printf("Will slepp 50\n");
        usleep(50);
    }
}
//sleep 
int	go_sleep(useconds_t usec)
{
	useconds_t		before;
	useconds_t		after;

	before = get_time_ms();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = get_time_ms();
	}
	return (0);
}
/////////////////////// SERVE FORK //////////////////////////////////
void    serve_fork(t_philo *philo)
{
    //printf("\nFORK, philo_id = %d\n", philo->id);
    //printf("Lock mutex to serve fork[%d] > philo->id - 1\n", philo->id -1);
    pthread_mutex_lock(&philo->data->fork[philo->id - 1]);  
    print_status(philo, "\033[1;94mhas taken a fork 🍴\033[0;39m");
    if (philo->id == philo->data->philo_nbr)
    {
        //printf("\nLock mutex to serve fork[0] -> if philo->id = philo_nbr = %d\n", philo->data->philo_nbr);
        pthread_mutex_lock(&philo->data->fork[0]);
    }
    else
    {
        //printf("\nLock mutex to serve fork[%d] > philo->id\n", philo->id);
        pthread_mutex_lock(&philo->data->fork[philo->id]);
    }
    print_status(philo, "\033[1;94mhas taken a fork 🍴\033[0;39m");
    update_list_id(philo->data, philo->id);
}

/////////////////////// EAT ///////////////////////////////////////
void    eating(t_philo *philo)
{
    //printf("\nEAT, philo_id = %d\n", philo->id);
    print_status(philo, "\033[1;93mis eating 🍝\033[0;39m");
    philo->last_meal = get_time_ms();
    philo->num_eaten++;
    //printf("philo eaten = %d\n", philo->num_eaten);

    //smart_sleep(philo->data->time_eat, philo);
    go_sleep(philo->data->time_eat);
    //printf("Unloock mutex after eat fork[%d] philo->id - 1\n", philo->id -1);
    pthread_mutex_unlock(&philo->data->fork[philo->id -1]);

    if (philo->id == philo->data->philo_nbr)
    {
        //printf("Unlock mutex after eat fork[0] -> if philo_id = philo_nbr = %d\n", philo->data->philo_nbr);
        pthread_mutex_unlock(&philo->data->fork[0]);
    }
    else
    {
        //printf("Unlock mutex after eat fork[%d] philo->id\n", philo->id);
        pthread_mutex_unlock(&philo->data->fork[philo->id]);
    }
}

/////////////// ROUTINE /////////////////////
void    *routine(void *philo_i)
{
    //printf("START ROUTINE\n\n");
    t_philo     *philo;
    pthread_t   threads;

    philo = philo_i;
    //printf("CREATE DEAD THREAD DETACHED\n");
    pthread_create(&threads, NULL, &is_dead, philo);
    pthread_detach(threads);
    while (philo->data->status == alive)
    {
        check_status(philo);
        if (philo->id != philo->data->list_id[0])
        {
            //printf(">> Continue, philo id = %d not list_id [0] = %d\n", philo->id, philo->data->list_id[0]);
            continue ;
        }
        if (philo->data->philo_nbr != 1)
        {
            serve_fork(philo);
            eating(philo);
            if (philo->data->num_eat 
                && philo->num_eaten == philo->data->num_eat)
                break;
            print_status(philo, "\033[1;95mis sleeping 🌙\033[0;39m");
            go_sleep(philo->data->time_sleep);
            //smart_sleep(philo->data->time_sleep, philo);
            print_status(philo, "\033[1;90mis thinking 💭\033[0;39m");
        }
        check_status(philo);
    }
    return (0);
}