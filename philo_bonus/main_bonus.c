/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:05:39 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/11 20:42:23 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	sem_wait(philo->sem_write);
	elapsed = gettime() - philo->start_simulation;
	if (status == TAKE_LEFT_FORK)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == TAKE_RIGHT_FORK)
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d is dead\n", elapsed, philo->id);
	sem_post(philo->sem_write);
}

int	init_semaphores(t_philo *philo)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal_check");
	sem_unlink("/death");
	philo->sem_forks = sem_open("/forks", O_CREAT, 0644, philo->philo_nbr);
	if (philo->sem_forks == SEM_FAILED)
		return (printf("Failed to open forks semaphore\n"), 1);
	philo->sem_write = sem_open("/write", O_CREAT, 0644, 1);
	if (philo->sem_write == SEM_FAILED)
		return (printf("Failled to open write semaphore\n"), 1);
	philo->sem_meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);
	if (philo->sem_meal_check == SEM_FAILED)
		return (printf("Failled to open meal check semaphore\n"), 1);
	philo->sem_death = sem_open("/death", O_CREAT, 0644, 1);
	if (philo->sem_death == SEM_FAILED)
		return (printf("Failled to open death semaphore\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (!(ac == 5 || ac == 6))
	{
		printf("Usage: ./philo_bonus [number_of_philosophers][time_to_die] ");
		printf("[time_to_eat][time_to_sleep][num_times_each_philo_must_eat]\n");
		return (1);
	}
	if (parse_input(&philo, av) != 0)
		return (1);
	if (init_semaphores(&philo) != 0)
		return (1);
	if (simulation(&philo) != 0)
		return (1);
	return (0);
}
