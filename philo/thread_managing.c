/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:01 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 12:43:18 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, &philo_routine,
				&table->philo[i]) != 0)
		{
			printf("Philos Thread creation failed\n");
			return (1);
		}
	}
	if (pthread_create(&table->monitor_thread, NULL, &monitor_routine,
			table) != 0)
	{
		printf("Monitor Thread creation failed\n");
		return (1);
	}
	return (0);
}

int	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->philo[i].thread_id, NULL) != 0)
		{
			printf("Thread join failed\n");
			return (1);
		}
	}
	if (pthread_join(table->monitor_thread, NULL) != 0)
	{
		printf("Monitor Thread join failed\n");
		return (1);
	}
	return (0);
}
