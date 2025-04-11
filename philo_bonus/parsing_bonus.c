/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:17:44 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/11 20:46:48 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static char	*valid_input(const char *str)
{
	int			len;
	const char	*res_str;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		exit_error("Error: Only positive numbers are allowed");
	res_str = str;
	while ((*str >= '0' && *str <= '9'))
	{
		len++;
		str++;
	}
	if (len > 10)
		exit_error("Error: the value is to big , INT_MAX is the limit\n");
	return ((char *)res_str);
}

static long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	str = valid_input(str);
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		exit_error("Error: the value is to big , INT_MAX is the limit\n");
	return (res);
}

int	parse_input(t_philo *philo, char **av)
{
	if (ft_atol(av[1]) > MAX_PHILOSOPHERS)
	{
		printf("Error: Number of philosophers must be less than 200\n");
		return (1);
	}
	philo->philo_nbr = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (philo->time_to_die < 60 || philo->time_to_sleep < 60
		|| philo->time_to_eat < 60)
	{
		printf("Error: time_to_die, time_to_sleep"
			"time_to_eat must be greater than 60 ms \n");
		return (1);
	}
	if (av[5])
		philo->nbr_limit_meal = ft_atol(av[5]);
	else
		philo->nbr_limit_meal = -1;
	return (0);
}
