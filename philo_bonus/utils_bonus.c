/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:26:07 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/11 20:45:10 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	exit_error(const char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

void	precise_usleep(long time)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime();
	while (1)
	{
		elapsed = gettime() - start;
		if (elapsed >= time)
			break ;
		remaining = time - elapsed;
		if (remaining > 500)
			usleep(500);
		else
			usleep(remaining);
	}
}

void	clean_semaphores(t_philo *philo)
{
	sem_close(philo->sem_forks);
	sem_close(philo->sem_write);
	sem_close(philo->sem_meal_check);
	sem_close(philo->sem_death);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal_check");
	sem_unlink("/death");
}
