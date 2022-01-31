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

////////////////// INIT FORK /////////////////////////
pthread_mutex_t *init_fork(t_data *data)
{
    //printf("INIT FORK\n");
    int i;
    pthread_mutex_t   *fork;

    i = 0;
    fork = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
    while (i < data->philo_nbr)
    {
        //printf("init_mutex_fork\n");
        //mutex -> protéger les données partagées (fork)
        pthread_mutex_init(&fork[i], NULL); //detroy
        i++;
    }
    return (fork);
}

///////////////// LIST /////////////////////////////////////////
int *init_list(t_data *data)
{
    //printf("INIT LIST\n");
    int *list_id;
    int philo_id;
    int i;

    i = 0;
    philo_id = 1;
    list_id = malloc(sizeof(int) * data->philo_nbr);
    while (philo_id <= data->philo_nbr)
    {
        list_id[i] = philo_id;
        //printf("i = %d, philo_id_1 = %d = list_id[i] = %d\n", i, philo_id, list_id[i]);
        philo_id += 2;
        i++;
    }
    philo_id = 2;
    while (philo_id <= data->philo_nbr)
    {
        list_id[i] = philo_id;
        //printf("i = %d, philo_id_2 = %d = list_id[i] = %d\n", i, philo_id, list_id[i]);
        i++;
        philo_id += 2;
    }

    /*printf("init list_id[i] = ");
    for(i = 0; i < data->philo_nbr; i++)
        printf("%d ", list_id[i]);
    printf("\n");*/
    return (list_id);
}

void    update_list_id(t_data *data, int philo_id)
{
    //printf("UPDATE list_id, philo_id = %d\n", philo_id);
    int i;

    i = 0;
    while (i < data->philo_nbr - 1)
    {
        data->list_id[i] = data->list_id[i + 1];
        i++;
    }
    data->list_id[i] = philo_id;

    /*printf("list_id[i] updated = ");
    for(i = 0; i < data->philo_nbr; i++)
        printf("%d ", data->list_id[i]);
    printf("\n");*/
}

////////////////// INIT DATA /////////////////////////////////////////////
t_data *parse_data(int argc, char **argv)
{
    //printf("INIT DATA \n");
    t_data  *data;

    data = malloc(sizeof(t_data));
    data->philo_nbr = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    //init time in ms
    data->launch_time = get_time_ms();
    //init fork
    data->fork = init_fork(data);
    data->list_id = init_list(data);
    data->status = alive;
    //printf("init_mutex_print\n");
    pthread_mutex_init(&data->print, NULL); //destroy
    if (argc == 6)
        data->num_eat = ft_atoi(argv[5]);
    else
        data->num_eat = 0;
    return (data);
}

////////////////////// INIT PHILO ///////////////////////////
t_philo *init_philos(t_data *data)
{
    //printf("INIT PHILO\n");
    t_philo *philo;
    int     i;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->philo_nbr);
    while (i < data->philo_nbr)
    {
        philo[i].id = i + 1;
        philo[i].data = data;
        philo[i].last_meal = 0;
        philo[i].num_eaten = 0;
        i++;
    }
    return (philo);
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
        printf("DEAD : philo_id %d DIEd, time_ms %lld\n", philo->id, time_ms);
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
        printf("STATUS : philo_id = %d, message : %s, time_ms = %lld\n", philo->id, str, time_ms);
    
    //printf("Unlock after print status\n");
    pthread_mutex_unlock(&philo->data->print);
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

/////////////////////// SERVE FORK //////////////////////////////////
void    serve_fork(t_philo *philo)
{
    //printf("\nFORK, philo_id = %d\n", philo->id);
    //printf("Lock mutex to serve fork[%d] > philo->id - 1\n", philo->id -1);
    pthread_mutex_lock(&philo->data->fork[philo->id - 1]);  
    print_status(philo, "has taken a fork");
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
    print_status(philo, "has taken a fork after 2");
    update_list_id(philo->data, philo->id);
}

/////////////////////// EAT ///////////////////////////////////////
void    eating(t_philo *philo)
{
    //printf("\nEAT, philo_id = %d\n", philo->id);
    print_status(philo, "is eating");
    philo->last_meal = get_time_ms();
    philo->num_eaten++;
    //printf("philo eaten = %d\n", philo->num_eaten);

    smart_sleep(philo->data->time_eat, philo);
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
            print_status(philo, "is sleeping");
            smart_sleep(philo->data->time_sleep, philo);
            print_status(philo, "is thinking");
        }
        check_status(philo);
    }
    return (0);
}

///////////////////// THREADS PER PHILO ///////////////////////////
int create_threads(t_philo *philo)
{
    pthread_t   *threads;
    int         i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * (philo->data->philo_nbr));
    while (i < philo->data->philo_nbr)
    {
        //printf("CREATE THREADS\n");
        pthread_create(&threads[i], NULL, routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < philo->data->philo_nbr)
    {
        pthread_join(threads[i], NULL);
        //printf("FINISH WAITING JOIN THREAD\n");
        i++;
    }
    free(threads);
    free(philo->data->fork);
    free(philo->data->list_id);
    free(philo->data);
    free(philo);
    return(0);
}

//////////////////// CHECK ARG ///////////////////////////
int check_arg(int argc, char **argv)
{
    if (argc > 4 && argc <= 6)
    {
        if (ft_atoi(argv[1]) < 1)
            return (printf("Need at least 1 philosopher.\n"));
        if (ft_atoi(argv[2]) < 1)
            return (printf("Time to die must be at least 1.\n"));
        if (ft_atoi(argv[3]) < 1)
            return (printf("Time to eat must be at least 1.\n"));
        if (ft_atoi(argv[4]) < 1)
            return (printf("Time to sleep must be at least 1.\n"));
        if (argc == 6 && ft_atoi(argv[5]) < 1)
            return (printf("Number of time to repeat must be at least 1.\n"));
    }
    else
		return (printf("Bad arguments :	[number_of_philosophers] [time_to_die] \
        [time_to_eat] [time_to_sleep]\nOPTIONAL :	\
        number_of_times_to_repeat]\n"));
    return (0);
}

int main(int argc, char **argv)
{
    t_data *data;
    t_philo *philo;
    
    if (check_arg(argc, argv) != 0)
        return (1);
    data = parse_data(argc, argv);
    philo = init_philos(data);
    create_threads(philo);
    return (0);
}
