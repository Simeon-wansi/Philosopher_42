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

static int	all_philos_have_eaten(t_philo *philo)
{
	int	i;

	if (philo->table->nbr_limit_meal == -1)
		return (0);
	i = -1;
	while (++i < philo->table->philo_nbr)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo[i].meal_counter < philo->table->nbr_limit_meal)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo->meal_mutex);
	}
	pthread_mutex_lock(philo->death_mutex);
	*philo->dead = true;
	pthread_mutex_unlock(philo->death_mutex);
	return (1);
}

static int	is_philos_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->meal_mutex);
	time = gettime() - philo->last_meal_time;
	if (time > philo->table->time_to_die && philo->is_eating == false)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

static int	check_dead_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->table->philo_nbr)
	{
		if (is_philos_dead(&philo[i]))
		{
			write_status(&philo[i], DIED);
			pthread_mutex_lock(philo->death_mutex);
			*philo->dead = true;
			pthread_mutex_unlock(philo->death_mutex);
			return (1);
		}
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	long	check_interval;
	t_table	*table;
	t_philo	*philos;

	table = (t_table *)arg;
	philos = table->philo;
	check_interval = table->time_to_die / 10;
	while (1)
	{
		if (check_dead_philos(philos) || all_philos_have_eaten(philos))
			break ;
		if (check_interval > 1000)
			usleep(check_interval);
		else
			usleep(1000);
	}
	return (arg);
}
