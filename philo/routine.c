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
		precise_usleep(philo->table->time_to_die);
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
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = true;
	philo->last_meal_time = gettime();
	philo->meal_counter++;
	if (philo->table->nbr_limit_meal != -1
		&& philo->meal_counter >= philo->table->nbr_limit_meal)
		philo->full = true;
	pthread_mutex_unlock(philo->meal_mutex);
	precise_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->meal_mutex);
	release_fork(philo);
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep);
	write_status(philo, THINKING);
}

int	philos_are_living(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead == true)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->table->time_to_eat);
	while (philos_are_living(philo))
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->table->nbr_limit_meal != -1
			&& philo->meal_counter >= philo->table->nbr_limit_meal)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->meal_mutex);
		eat_sleep_think(philo);
		if (philo->table->philo_nbr == 1)
			break ;
	}
	return (arg);
}
