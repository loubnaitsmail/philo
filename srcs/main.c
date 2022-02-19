#include "philo.h"

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

//////////////////// CHECK ARG ///////////////////////////
int check_arg(int argc, char **argv)
{
    if (argc > 4 && argc <= 6)
    {
        if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
            return (printf("Need at least 1 philosopher and no more then 200.\n"));
        if (ft_atoi(argv[2]) < 1)
            return (printf("Time to die must be at least 1.\n"));
        if (ft_atoi(argv[3]) < 1)
            return (printf("Time to eat must be at least 1.\n"));
        if (ft_atoi(argv[4]) < 60)
            return (printf("Time to sleep must be at least 60ms.\n"));
        if (argc == 6 && ft_atoi(argv[5]) < 1)
            return (printf("Number of time to repeat must be at least 1.\n"));
    }
    else
		return (printf("Bad arguments :[number_of_philosophers][time_to_die][time_to_eat][time_to_sleep]\nOPTIONAL : number_of_times_to_repeat]\n"));
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
