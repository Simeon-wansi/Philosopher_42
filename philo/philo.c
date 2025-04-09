/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:04:37 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/01 21:24:58 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosopher.h"
// #include <math.h>
// 
// 
// // int	simulation(t_table *table)
// {
// 	pthread_t	monitor_thread;
// 	int			id;

// 	id = -1;
// 	table->start_simulation = gettime();

// 	while (++id < table->philo_nbr)
// 		table->philo[id].last_meal_time = table->start_simulation;
// 	// create the thread of each philos
// 	id = -1;
// 	while (++id < table->philo_nbr)
// 	{
// 		if (pthread_create(&table->philo[id].thread_id, NULL, philo_routine,
// 				&table->philo[id]))
// 			exit_error("Thread creation failed\n");
// 		// table->philo[id].last_meal_time = gettime();
// 	}
// 	// create the thread of the monitor
// 	if (pthread_create(&monitor_thread, NULL, monitor_routine, table))
// 		exit_error("Monitor Thread creation failed\n");
// 	join_threads(table, monitor_thread);
// 	usleep(1000);
// 	return (0);
// }

// int join_threads(t_table *table, pthread_t monitor_thread)
// {
// 	int i;
	// 
// 	i = -1;
// 	while (++i < table->philo_nbr)
// 	{
// 		if (pthread_join(table->philo[i].thread_id, NULL))
// 			exit_error("Thread join failed\n");
// 	}
// 	if (pthread_join(monitor_thread, NULL))
// 		exit_error("Monitor Thread join failed\n");
// 	return(EXIT_SUCCESS);
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;
// 	int		first_fork;
// 	int		second_fork;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		usleep(philo->table->time_to_eat / 10);
		// 
// 	while (!philo->full && !is_simulation_over(philo->table))
// 	{
// 		first_fork = fmin(philo->left_fork, philo->right_fork);
// 		second_fork = fmax(philo->left_fork, philo->right_fork);
		// 
// 		pthread_mutex_lock(&philo->table->fork_mutex[first_fork]);
// 		if (is_simulation_over(philo->table))
// 		{
// 			pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
// 			break;
// 		}
// 		write_status(philo, TAKE_LEFT_FORK);
// 		if (philo->table->philo_nbr == 1)
// 		{
// 			pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
// 			precise_usleep(philo->table->time_to_die, philo->table);	
// 			break;
// 		}
// 		// if(is_simulation_over(philo->table))
// 		// 	break;
// 		pthread_mutex_lock(&philo->table->fork_mutex[second_fork]);
// 		if (philo->table->philo_nbr == 1)
// 		{
// 			pthread_mutex_unlock(&philo->table->fork_mutex[second_fork]);
// 			precise_usleep(philo->table->time_to_die, philo->table);	
// 			break;
// 		}
// 		write_status(philo, TAKE_RIGHT_FORK);
// 		eat(philo);
// 		pthread_mutex_unlock(&philo->table->fork_mutex[second_fork]);
// 		pthread_mutex_unlock(&philo->table->fork_mutex[first_fork]);
//         // if(is_simulation_over(philo->table))
// 		// 	break;
// 		sleeping(philo);
// 		// if(is_simulation_over(philo->table))
// 		// 	break;
//         thinking(philo);
// 	}
// 	return (NULL);
// }

// 
// static void	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->philo_mutex);
// 	philo->last_meal_time = gettime();
// 	philo->meal_counter++;
// 	write_status(philo, EATING);
// 	if (philo->meal_counter == philo->table->nbr_limit_meal)
// 		philo->full = true;
// 	pthread_mutex_unlock(&philo->philo_mutex);
	// 
// 	precise_usleep(philo->table->time_to_eat, philo->table);
	// 
// }

// void	sleeping(t_philo *philo)
// {
// 	write_status(philo, SLEEPING);
// 	precise_usleep(philo->table->time_to_sleep, philo->table);
// }

// void	thinking(t_philo *philo)
// {
// 	write_status(philo, THINKING);
// 
