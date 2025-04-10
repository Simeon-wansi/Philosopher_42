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

	pthread_mutex_lock(&philo->table->write_mutex);
	elapsed = gettime() - philo->table->start_simulation;
	if (philo->full)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (status == TAKE_LEFT_FORK && !philo->table->death)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == TAKE_RIGHT_FORK && !philo->table->death)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
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

void	cleanup_ressources(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->fork_mutex[i]);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
	}
	// pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->time_mutex);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!(ac == 5 || ac == 6))
	{
		printf("Error :Do./philo [number_of_philos][time_to_die][time_to_eat]");
		printf("[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
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
