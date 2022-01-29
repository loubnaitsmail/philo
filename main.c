#include "philo.h"

//get launch time in ms
long long   get_time_ms()
{
    struct timeval  tv;
    long long       launch_time_ms;

    gettimeofday(&tv, NULL);
    launch_time_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    printf("launch time ms = %lld\n", launch_time_ms);
    return(launch_time_ms);
}

//mutex -> protéger les données partagées (fork)
pthread_mutex_t *init_fork(t_data *data)
{
    int i;
    pthread_mutex_t   *fork;

    i = 0;
    fork = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
    while (i < data->philo_nbr)
    {
        pthread_mutex_init(&fork[i], NULL); //detroy
        i++;
    }
    return (fork);
}

t_data *parse_data(int argc, char **argv)
{
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
    data->status = alive;
    pthread_mutex_init(&data->print, NULL); //destroy
    //list

    if (argc == 6)
        data->repeat = ft_atoi(argv[5]);
    else
        data->repeat = 0;
    
    /*printf("nbr_philo = %d\n", data->philo_nbr);
    printf("time to die= %d\n", data->time_die);
    printf("time to eat = %d\n", data->time_eat );
    printf("time to sleep = %d\n", data->time_sleep);
    printf("nbr of repeat  = %d\n", data->repeat);*/

    return (data);
}

t_philo *init_philos(t_data *data)
{
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

//////////////////////////////////////////////////////
void    print_dead(t_philo *philo)
{
    long long   time_ms;

    printf("Lock to print dead\n");
    pthread_mutex_lock(&philo->data->print);
    time_ms = get_time_ms() - philo->data->launch_time;
    if (philo->data->status == alive)
    {
        philo->data->status = dead;
        printf("will sleep\n");
        usleep(1000);
        printf("time_ms %lld, philo id %d died\n", time_ms, philo->id);
    }
    printf("Unlock after print dead\n");
    pthread_mutex_unlock(&philo->data->print);
}

t_status    check_status(t_philo    *philo)
{
    printf("check status func\n");
    long long   time_ms;

    time_ms = get_time_ms();
    if (philo->last_meal == 0)
        philo->last_meal = get_time_ms() - 1;
    printf("last meal was 0 -> %lld\n", philo->last_meal);

    if (philo->data->status == dead)
        return (dead);
    if (time_ms - philo->last_meal > philo->data->time_die)
    {
        print_dead(philo);
        return (dead);
    }
    return (alive);
}

void    *is_dead(void *philo_i)
{
    printf("is dead func\n");
    t_philo *philo;

    philo = philo_i;
    while (1)
        check_status(philo);
}

/////////////////////////////////////////////////////////////////////
void    print_status(t_philo *philo, char *str)
{
    long long   time_ms;

    printf("\nLock to print status, id = %d\n", philo->id);
    pthread_mutex_lock(&philo->data->print);

    time_ms = get_time_ms() - philo->data->launch_time;

    if (philo->data->status == alive)
        printf("***print time_ms = %lld, philo_id = %d, %s\n", time_ms, philo->id, str);
    
    printf("Unlock after print status\n\n");
    pthread_mutex_unlock(&philo->data->print);
}

void    serve_fork(t_philo *philo)
{
    printf("\nLock to serve fork [philo->id - 1] = %d\n", philo->id - 1);
    pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
    
    print_status(philo, "has taken a fork");

    if (philo->id == philo->data->philo_nbr)
    {
        printf("if id = philo_nbr -> Lock fork [0]\n");
        pthread_mutex_lock(&philo->data->fork[0]);
    }
    else
    {
        printf("Else -> Lock fork [philo->id] = %d\n", philo->id);
        pthread_mutex_lock(&philo->data->fork[philo->id]);
    }
    print_status(philo, "has taken a fork after");
    //update_list();
}

void    *routine(void *philo_i)
{
    t_philo     *philo;
    pthread_t   threads;

    philo = philo_i;
    //pthread_create(&threads, NULL, &is_dead, philo);
    //pthread_detach(threads);

    while (philo->data->status == alive)
    {
        //check_status(philo);
        //if (philo->id )

        if (philo->data->philo_nbr != 1)
        {
            serve_fork(philo);
            //eat
            //sleep

        }
    }
    return (0);
}

int create_threads(t_philo *philo)
{
    pthread_t   *threads;
    int         i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * philo->data->philo_nbr);
    while (i < philo->data->philo_nbr)
    {
        pthread_create(&threads[i], NULL, routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < philo->data->philo_nbr)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
    free(philo->data->fork);
      //free list
    free(philo->data);
    free(philo);
    return(0);
}

int main(int argc, char **argv)
{
    t_data *data;
    t_philo *philo;
    //check_arg;
    if (argc != 6)
		printf("bad arg : nbr_philo, time to die, time to eat, time to sleep,\n");

    //parse data
    data = parse_data(argc, argv);
    //init philo
    philo = init_philos(data);
    //create threads
    create_threads(philo);

    //return (0);
}
