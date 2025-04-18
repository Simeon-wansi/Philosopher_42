/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:21:36 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 21:18:30 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h> 
# define MAX_PHILOSOPHERS 200

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	t_table				*table;

	bool				full;
	bool				is_eating;
	long				meal_counter;
	long				last_meal_time;
	int					right_fork;
	int					left_fork;
	bool				*dead;
	t_mutex				*write_mutex;
	t_mutex				*death_mutex;
	t_mutex				*meal_mutex;
}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meal;
	long				start_simulation;
	bool				dead;
	bool				all_ate;
	t_mutex				*fork_mutex;
	t_philo				*philo;
	t_mutex				write_mutex;
	t_mutex				death_mutex;
	t_mutex				meal_mutex;
	pthread_t			monitor_thread;
}						t_table;

typedef enum s_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED
}						t_philo_status;

/*Init func*/
int						data_init(t_table *table);

/*Parsing func*/
int						parse_input(t_table *table, char **av);
void					exit_error(const char *str);
long					gettime(void);

/*threads*/
int						create_threads(t_table *table);
int						join_threads(t_table *table);

/*Utils func*/
int						precise_usleep(long time);

void					write_status(t_philo *philo, t_philo_status status);
int						find_min(int a, int b);
int						find_max(int a, int b);
void					cleanup_ressources(t_table *table);

/*Monitor*/
void					*monitor_routine(void *arg);
int						philos_are_living(t_philo *philo);

/*Routine*/
void					*philo_routine(void *arg);
int						philos_are_living(t_philo *philo);
#endif
