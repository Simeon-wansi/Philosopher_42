/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:36:13 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 08:29:57 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_philo_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->philo_mutex);
	time = gettime() - philo->last_meal_time;
	if (time > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

static int	check_dead_philos(t_table *table)
{
	int	i;

	i = 0;
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (is_philo_dead(&table->philo[i]))
		{
			write_status(&table->philo[i], DIED);
			pthread_mutex_lock(&table->death_mutex);
			table->death = true;
			pthread_mutex_unlock(&table->death_mutex);
			return (1);
		}
	}
	return (0);
}

static int	all_philos_have_eatean(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meal == -1)
		return (0);
	while (++i < table->philo_nbr)
	{
		if (table->philo[i].full == false)
			return (0);
	}
	pthread_mutex_lock(&table->monitor_mutex);
	table->all_ate = true;
	pthread_mutex_unlock(&table->monitor_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_dead_philos(table) || all_philos_have_eatean(table))
			break ;
	}
	return (arg);
}
// void	*monitor_routine(void *arg)
// {
// 	t_table *table;
// 	long current_time;
// 	int i;

// 	table = (t_table *)arg;
// 	while (1)
// 	{
// 		printf("Debug Strart monitor\n");
// 		i = -1;
// 		while (++i < table->philo_nbr )
// 		{
// 			pthread_mutex_lock(&table->philo[i].philo_mutex);
// 			current_time = gettime();
// 			// Now we check if the philosopher has died
// 			if ((current_time
// 					- table->philo[i].last_meal_time) > table->time_to_die)
// 			{
// 				printf("Debug in monitor\n");
// 				pthread_mutex_lock(&table->table_mutex);
// 				if (!table->death)
// 				{
// 					table->death = true;
// 					write_status(&table->philo[i], DIED);
// 					usleep(100);
// 				}
// 				pthread_mutex_unlock(&table->table_mutex);
// 			}
// 			pthread_mutex_unlock(&table->philo[i].philo_mutex);
// 		}
// 		// We check if all philosopher are full
// 		if (all_philosopher_full(table))
// 			table->all_ate = true;
// 		if (is_simulation_over(table))
// 			break ;
// 		usleep(100);
// 		printf("Debug End monitor\n");
// 	}
// 	return (arg);
// }

// bool	all_philosopher_full(t_table *table)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < table->philo_nbr && table->nbr_limit_meal != -1)
// 	{
// 		if (!table->philo[i].full)
// 			return (false);
// 	}
// 	return (true);
// }
