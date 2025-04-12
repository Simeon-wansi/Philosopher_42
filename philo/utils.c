/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:23:26 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/01 21:30:19 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	exit_error(const char *str)
{
	printf("%s\n", str);
	exit(1);
}

long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1e3) + (t.tv_usec / 1e3));
}

void	precise_usleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime();
	while (!get_simulation_end(table))
	{
		elapsed = gettime() - start;
		if (elapsed >= time)
			break ;
		remaining = time - elapsed;
		if (remaining > 1e3)
			usleep(1e3);
		else
			usleep(remaining);
	}
}

int	find_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	find_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
