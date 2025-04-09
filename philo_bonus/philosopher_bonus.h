/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:07:51 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 08:52:34 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philo
{
    int                 id;
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meal;
    long                 last_meal_time;

    int                  meal_count;
    long                 start_simulation;
    
    sem_t               *sem_forks;
    sem_t               *sem_write;
    sem_t               *sem_meal_check;
	sem_t               *sem_death;
    
    pid_t               pids[MAX_PHILOSOPHERS];
    
}               t_philo;

typedef enum s_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED
}		t_philo_status;


int	parse_input(t_philo *philo, char **av);
int init_semaphores(t_philo *philo);
int simulation(t_philo *philo);

/* Utils func*/
long	gettime(void);

void	write_status(t_philo *philo, t_philo_status status);

void wait_for_simulation_to_end(t_philo *philo);
void *death_monitor(void *arg);
void	precise_usleep(long time);

#endif