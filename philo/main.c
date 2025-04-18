/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:10:18 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 21:35:20 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->death_mutex);
	pthread_mutex_lock(philo->write_mutex);
	if (philos_are_living(philo))
	{
		elapsed = gettime() - philo->table->start_simulation;
		if (status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d is dead\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(philo->write_mutex);
}

void	cleanup_ressources(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_destroy(&table->fork_mutex[i]) != 0)
			exit_error("Error: Detroy mutex failed");
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	free(table->philo);
	free(table->fork_mutex);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
	{
		printf("❌Error: Do./philo [number_of_philo][time_to_die][time_to_eat]");
		printf("[time_to_sleep][number_of_times_each_philosopher_must_eat]");
		return (1);
	}
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
	return (0);
}
