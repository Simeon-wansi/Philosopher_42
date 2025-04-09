/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:11 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 08:53:11 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"


int init_semaphores(t_philo *philo)
{
    // I have to clean the previous semaphores from previous run
    sem_unlink("/forks");
    sem_unlink("/write");
    sem_unlink("/meal_check");
    sem_unlink("/death");

    // Now I open fork smaephores: number of forks = num of philo
    philo->sem_forks = sem_open("/forks", O_CREAT, 0644, philo->philo_nbr);
    if (philo->sem_forks ==  SEM_FAILED)
        return (printf("Failed to open forks semaphore\n"), 1);
    
    //Now I open write semaphores 
    philo->sem_write = sem_open("/write", O_CREAT, 0644, 1);
    if (philo->sem_write ==  SEM_FAILED)
        return(printf("Failled to open write semaphore\n"), 1);

    philo->sem_meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);
    if (philo->sem_meal_check == SEM_FAILED)
        return (printf("Failled to open meal check semaphore\n"), 1);
    
    philo->sem_death = sem_open("/death", O_CREAT, 0644, 1);
    if (philo->sem_death == SEM_FAILED)
        return (printf("Failled to open death semaphore\n"), 1);
    return (0);
}