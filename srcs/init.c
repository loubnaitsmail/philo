#include "philo.h"

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