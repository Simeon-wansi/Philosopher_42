/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:29:01 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 21:18:47 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	mutex_initialisation(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->write_mutex, NULL) != 0
		|| pthread_mutex_init(&table->death_mutex, NULL) != 0
		|| pthread_mutex_init(&table->meal_mutex, NULL) != 0)
	{
		printf("Mutex initialisation failed\n");
		return (1);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL) != 0)
		{
			printf("Mutex initialisation failed\n");
			return (1);
		}
	}
	return (0);
}

static void init_philos(t_table *table)
{
	int	i;
	t_philo *philos;

	philos = table->philo;
	i = -1;
	while (++i < table->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].is_eating =  false;
		philos[i].meal_counter = 0;
		philos[i].full = false;
		philos[i].last_meal_time = gettime();
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % table->philo_nbr;
		philos[i].dead = &table->dead;
		philos[i].death_mutex = &table->death_mutex;
		philos[i].write_mutex = &table->write_mutex;
		philos[i].meal_mutex = &table->meal_mutex;
	}
}

int	data_init(t_table *table)
{
	
	if (mutex_initialisation(table) != 0)
		return (1);
	table->dead = false;
	table->all_ate = false;
	table->start_simulation = gettime();
	init_philos(table);
	return (0);
}
