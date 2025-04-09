/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:26:07 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 09:10:59 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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