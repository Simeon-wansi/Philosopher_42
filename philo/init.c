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

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL) != 0
			|| pthread_mutex_init(&table->philo[i].philo_mutex, NULL) != 0
			|| pthread_mutex_init(&table->philo[i].meal_mutex, NULL) != 0)
		{
			printf("Mutex initialisation failed\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0
		|| pthread_mutex_init(&table->stop_mutex, NULL) != 0
		|| pthread_mutex_init(&table->time_mutex, NULL) != 0)
	{
		printf("Mutex initialisation failed\n");
		return (1);
	}
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	if (mutex_initialisation(table) != 0)
		return (1);
	while (++i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meal_counter = 0;
		table->philo[i].full = false;
		table->philo[i].last_meal_time = gettime();
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philo_nbr;
	}
	table->death = false;
	table->all_ate = false;
	table->start_simulation = gettime();
	return (0);
}
