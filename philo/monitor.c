/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:36:13 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/10 14:55:15 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	get_simulation_end(t_table *table)
{
	bool	ret;

	pthread_mutex_lock(&table->stop_mutex);
	ret = table->death;
	pthread_mutex_unlock(&table->stop_mutex);
	return (ret);
}

static int	all_philos_have_eaten(t_table *table)
{
	int	i;
	int	all_full;

	if (table->nbr_limit_meal == -1)
		return (0);
	all_full = 1;
	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		if (!table->philo[i].full)
			all_full = 0;
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		if (!all_full)
			break ;
	}
	if (all_full)
	{
		pthread_mutex_lock(&table->stop_mutex);
		table->all_ate = true;
		pthread_mutex_unlock(&table->stop_mutex);
		return (1);
	}
	return (0);
}

static int	check_philosopher_death(t_table *table, int i)
{
	long	time;
	int		ret;

	ret = 0;
	pthread_mutex_lock(&table->philo[i].philo_mutex);
	pthread_mutex_lock(&table->time_mutex);
	time = gettime() - table->philo[i].last_meal_time;
	if (time > table->time_to_die && !get_simulation_end(table))
	{
		write_status(&table->philo[i], DIED);
		pthread_mutex_lock(&table->stop_mutex);
		table->death = true;
		pthread_mutex_unlock(&table->stop_mutex);
		ret = 1;
	}
	pthread_mutex_unlock(&table->time_mutex);
	pthread_mutex_unlock(&table->philo[i].philo_mutex);
	return (ret);
}

static int	check_dead_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (check_philosopher_death(table, i))
			return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_dead_philos(table) || all_philos_have_eaten(table))
			break ;
		usleep(1000);
	}
	return (arg);
}
