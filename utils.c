
#include "philosopher.h"

void exit_error(const char *str)
{
	printf("%s\n", str);
    exit(1);
}

long gettime(void)
{
	struct  timeval t;
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

void precise_usleep(long time, t_table *table)
{
	long start;
	long elapsed;
	long remaining;

	start  =  gettime();
	// printf("Debug: start = %ld\n", start);
	// printf("Debug: time = %ld\n", time);
	while(!table->death)
	{
		elapsed = gettime() - start;
		if (elapsed >= time)
			break;
		remaining = time - elapsed;
		if (remaining > 1e3)
			usleep(1e3);
		else
			usleep(remaining);
	}
	// printf("Debug: end = %ld\n", gettime());
	// printf("Debug: elapsed = %ld\n", gettime() - start);
}

void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	elapsed = gettime() - philo->table->start_simulation;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (status == TAKE_LEFT_FORK && !philo->table->death)
		printf("%ld %d has taken the left fork\n", elapsed, philo->id);
	else if (status == TAKE_RIGHT_FORK && !philo->table->death)
		printf("%ld %d has taken the right fork\n", elapsed, philo->id);
	else if (status == EATING && !philo->table->death)
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !philo->table->death)
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !philo->table->death)
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d is dead\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void cleanup_ressources(t_table *table)
{
    int i;

    i = -1;
    while(++i < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->fork_mutex[i]);
        pthread_mutex_destroy(&table->philo[i].philo_mutex);
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
    }
    pthread_mutex_destroy(&table->table_mutex);
    pthread_mutex_destroy(&table->write_mutex);
}