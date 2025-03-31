
#include "philosopher.h"

int main(int ac, char **av)
{
    t_table table;
    if (ac == 5 || ac == 6)
    {
        if (parse_input(&table, av) != 0)
            return (1);
        if (data_init(&table) != 0)
            return (1);
        if (create_threads(&table) != 0)
        {
            cleanup_ressources(&table);
            return (1);
        }
        if (join_threads(&table) != 0)
        {
            cleanup_ressources(&table);
            return (1);
        }
        cleanup_ressources(&table);
    }
    else
    {
        exit_error("Wrong input \n"
            "Do ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
    }
    return (0);
}
