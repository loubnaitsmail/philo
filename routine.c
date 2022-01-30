



void    *is_dead(void *philo_i)
{
    printf("is dead func\n");
    t_philo *philo;

    philo = philo_i;
    while (1)
        check_status(philo);

return (0);
}
