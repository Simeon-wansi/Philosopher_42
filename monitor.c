/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:36:13 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/31 16:09:01 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

static int is_philo_dead(t_philo *philo)
{
    long time;

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

static int check_dead_philos(t_philo *philos)
{
    int i = 0;

    i = -1;
    while(++i < philos->table->philo_nbr)
    {
        if (is_philo_dead(&philos[i]))
        {
            write_status(&philos[i], DIED);
            pthread_mutex_lock(&philos->table->table_mutex);
            philos->table->death = true;
            pthread_mutex_unlock(&philos->table->table_mutex);
            return (1);
        }
    }
    return (0);
}

static int all_phios_have_eatean(t_philo *philos)
{
    int i;

    i = -1;
    while(++i < philos->table->philo_nbr)
    {
        pthread_mutex_lock(&philos[i].philo_mutex);
        if (philos[i].meal_counter < philos[i].table->nbr_limit_meal)
        {
            pthread_mutex_unlock(&philos[i].philo_mutex);
            return (0);
        }
        pthread_mutex_unlock(&philos[i].philo_mutex);
    }
    pthread_mutex_lock(&philos->table->table_mutex);
    philos->table->all_ate = true;
    pthread_mutex_unlock(&philos->table->table_mutex);
    return (1);
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    
    philos = (t_philo *)arg;
    
    while(1)
    {
        if (check_dead_philos(philos) || all_phios_have_eatean(philos))
            break;
    }
    return(arg);
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
// 			break;
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
