/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:05:39 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 14:08:05 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"


void	write_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;
	
	// elapsed = gettime() - philo->start_simulation;
	// printf("[DEBUG] time=%ld | message: %u\n", elapsed, status);

	// if (philo->full)
	// 	return ;
	// pthread_mutex_lock(&philo->table->write_mutex);
    sem_wait(philo->sem_write);
	elapsed = gettime() - philo->start_simulation;
	// printf("Philo No %d has a elapsed = %ld\n", philo->id, elapsed);
	if (status == TAKE_LEFT_FORK )
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


int main(int ac, char **av)
{
    t_philo philo;

    if (!(ac == 5 || ac == 6))
    {
        printf("Usage: ./philo_bonus [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n");
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
