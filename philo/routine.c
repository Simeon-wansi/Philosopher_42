/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:55:23 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 21:19:21 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	fork_assign(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = find_min(philo->left_fork, philo->right_fork);
	second_fork = find_max(philo->left_fork, philo->right_fork);
	pthread_mutex_lock(&philo->table->fork_mutex[first_fork]);
	write_status(philo, TAKE_LEFT_FORK);
	if (philo->table->philo_nbr == 1)
	{
		precise_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->table->fork_mutex[second_fork]);
	write_status(philo, TAKE_RIGHT_FORK);
	return (0);
}

static void	release_fork(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = find_min(philo->left_fork, philo->right_fork);
	second_fork = find_max(philo->left_fork, philo->right_fork);
	pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[second_fork]);
}

static void	eat_sleep_think(t_philo *philo)
{
	if (fork_assign(philo) != 0)
		return ;
	write_status(philo, EATING);
	philo->is_eating = true; // Move this
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = gettime();
	precise_usleep(philo->table->time_to_eat, philo->table);
	philo->meal_counter++;
	if (philo->meal_counter == philo->table->nbr_limit_meal)
		philo->full = true;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo->is_eating = false; // Move this
	release_fork(philo);
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
	write_status(philo, THINKING);
}

bool	is_simulation_over(t_table *table)
{
	bool res;
	
	pthread_mutex_lock(&table->stop_mutex);
	res = table->death || table->all_ate;
	pthread_mutex_unlock(&table->stop_mutex);
	return (res);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->table->time_to_eat / 2, philo->table);
	while (!is_simulation_over(philo->table))
	{
		eat_sleep_think(philo);
		if (philo->table->philo_nbr == 1)
			break ;
	}
	return (arg);
}
