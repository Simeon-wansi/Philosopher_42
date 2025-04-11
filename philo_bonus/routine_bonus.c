/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:07:31 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/11 21:40:33 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	write_status(philo, TAKE_LEFT_FORK);
	sem_wait(philo->sem_forks);
	write_status(philo, TAKE_RIGHT_FORK);
	write_status(philo, EATING);
	sem_wait(philo->sem_death);
	philo->last_meal_time = gettime();
	sem_post(philo->sem_death);
	precise_usleep(philo->time_to_eat);
	philo->meal_count++;
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
}

static void	start_philosopher(t_philo *philo, int i)
{
	pthread_t	monitor_thread;

	philo->id = i + 1;
	sem_wait(philo->sem_death);
	philo->last_meal_time = gettime();
	sem_post(philo->sem_death);
	philo->meal_count = 0;
	if (pthread_create(&monitor_thread, NULL, &death_monitor, philo) != 0)
		exit_error("Error: Thread creation failed");
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(philo);
		if (philo->nbr_limit_meal != -1
			&& philo->meal_count >= philo->nbr_limit_meal)
			exit(0);
		write_status(philo, SLEEPING);
		precise_usleep(philo->time_to_sleep);
		write_status(philo, THINKING);
	}
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->sem_death);
		if ((gettime() - philo->last_meal_time) > philo->time_to_die)
		{
			write_status(philo, DIED);
			sem_post(philo->sem_death);
			exit(1);
		}
		sem_post(philo->sem_death);
		usleep(1000);
	}
	return (NULL);
}

void	wait_for_simulation_to_end(t_philo *philo)
{
	int	status;
	int	exit_count;
	int	i;

	exit_count = 0;
	while (exit_count < philo->philo_nbr)
	{
		waitpid(-1, &status, 0);
		if ((status >> 8) == 1)
		{
			i = -1;
			while (++i < philo->philo_nbr)
				kill(philo->pids[i], SIGKILL);
			break ;
		}
		else
			exit_count++;
	}
	clean_semaphores(philo);
}

int	simulation(t_philo *philo)
{
	int	i;

	i = -1;
	philo->start_simulation = gettime();
	while (++i < philo->philo_nbr)
	{
		philo->pids[i] = fork();
		if (philo->pids[i] < 0)
			return (printf("Error: fork failed\n"), 1);
		if (philo->pids[i] == 0)
		{
			start_philosopher(philo, i);
			exit(0);
		}
		usleep(1000);
	}
	wait_for_simulation_to_end(philo);
	return (0);
}
