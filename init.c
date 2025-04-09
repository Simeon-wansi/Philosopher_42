
#include "philosopher.h"

int	data_init(t_table *table)
{
	int i;

	i = -1;
	// we initialize fork mutex
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL) != 0 ||
			pthread_mutex_init(&table->philo[i].philo_mutex, NULL) != 0 ||
			pthread_mutex_init(&table->philo[i].meal_mutex, NULL) != 0)
		{
			printf("Mutex initialisation failed\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0 ||
		pthread_mutex_init(&table->write_mutex, NULL) != 0 ||
		pthread_mutex_init(&table->monitor_mutex, NULL) != 0 ||
		pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		printf("Mutex initialisation failed\n");
		return (1);
	}

	// we initialize philos
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meal_counter = 0;
		table->philo[i].full = false;
		table->philo[i].is_eating = false;
		table->philo[i].last_meal_time = gettime();

		// assignation of fork in a circular arragement
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philo_nbr;
	}
	table->death = false;
	table->all_ate = false;
	table->start_simulation =  gettime();
	// printf("Debug : table->start_simulation = %ld\n", table->start_simulation);
	// printf("Debug : table->time_to_die = %ld\n", table->time_to_die);
	// printf("Debug : table->time_to_sleep = %ld\n", table->time_to_sleep);
	// printf("Debug : table->time_to_eat = %ld\n", table->time_to_eat);
	// printf("Debug : table->philo_nbr = %ld\n", table->philo_nbr);
	// printf("Debug : table->nbr_limit_meal = %ld\n", table->nbr_limit_meal);

	return (0);
}