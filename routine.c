/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:55:23 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/31 19:31:52 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <math.h>

static void eat_sleep_think(t_philo *philo)
{
    int		first_fork;
	int		second_fork;

    first_fork = fmin(philo->left_fork, philo->right_fork);
	second_fork = fmax(philo->left_fork, philo->right_fork);
    pthread_mutex_lock(&philo->table->fork_mutex[first_fork]);
    write_status(philo, TAKE_LEFT_FORK);
    // printf("Debug : philo nb %ld\n", philo->table->philo_nbr);
    if (philo->table->philo_nbr == 1)
    {
        precise_usleep(philo->table->time_to_die, philo->table);
        pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
        return ;
    }
    pthread_mutex_lock(&philo->table->fork_mutex[second_fork]);
    write_status(philo, TAKE_RIGHT_FORK);
    write_status(philo, EATING);
    philo->is_eating = true;
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = gettime();
    philo->meal_counter++;
    if (philo->meal_counter == philo->table->nbr_limit_meal)
        philo->full = true;
    // printf("debug :%ld %d has taken a fork\n", gettime(), philo->id);
    pthread_mutex_unlock(&philo->meal_mutex);
    precise_usleep(philo->table->time_to_eat, philo->table);
    philo->is_eating = false;
    pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
    pthread_mutex_unlock(&philo->table->fork_mutex[second_fork]);
    write_status(philo, SLEEPING);
    precise_usleep(philo->table->time_to_sleep, philo->table);
    write_status(philo, THINKING);    
}
bool is_simulation_over(t_table *table)
{

	pthread_mutex_lock(&table->table_mutex);
    
	if (table->death || table->all_ate)
    {
        pthread_mutex_unlock(&table->table_mutex);
        return (true);
    }
	pthread_mutex_unlock(&table->table_mutex);
	return (false);
}
void *philo_routine(void *arg)
{
    t_philo *philos;

    philos = (t_philo *)arg;
    
    if (philos->id % 2 == 0)
        precise_usleep(philos->table->time_to_eat / 2, philos->table);
    while(!is_simulation_over(philos->table))
    {
        eat_sleep_think(philos);
        if (philos->table->philo_nbr == 1)
            break;
    }
    return (arg); 
}

