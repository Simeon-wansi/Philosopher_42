/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:07:31 by sngantch          #+#    #+#             */
/*   Updated: 2025/04/09 14:00:11 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"


static void start_philosopher(t_philo *philo, int i)
{
    pthread_t monitor_thread;
    
    //initialisae this philosopher
    philo->id = i + 1;
    philo->last_meal_time = gettime();
    philo->meal_count = 0;
    

    //I start the monitoring thread to check for death
    pthread_create(&monitor_thread, NULL, &death_monitor, philo);
    pthread_detach(monitor_thread); // wait for the thread to end and free resources

    if (philo->id % 2 == 0)
        usleep(1000);
 
    while (1)
    {
        //taking forks
        sem_wait(philo->sem_forks);
        write_status(philo, TAKE_LEFT_FORK);
        
        sem_wait(philo->sem_forks);
        write_status(philo, TAKE_RIGHT_FORK);
        
        //eating
        // sem_wait(philo->sem_meal_check);
        write_status(philo, EATING);
        philo->last_meal_time = gettime();
        precise_usleep(philo->time_to_eat);
        philo->meal_count++;
        // sem_post(philo->sem_meal_check);
        
        sem_post(philo->sem_forks);
        sem_post(philo->sem_forks);
        
        // printf("Debug: Philo %d | meal_count: %d | last_meal: %ld | now: %ld\n",
        //     philo->id, philo->meal_count, philo->last_meal_time, gettime());
        
        //stop the process if the meal limit is reached
        if(philo->nbr_limit_meal != -1 && philo->meal_count >= philo->nbr_limit_meal)
            exit(0);
        
        //sleeping
        write_status(philo, SLEEPING);
        precise_usleep(philo->time_to_sleep);

        //thinking
        write_status(philo, THINKING);
    }
}




void *death_monitor(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    
    while(1)
    {
        sem_wait(philo->sem_death);
        if (gettime() - philo->last_meal_time > philo->time_to_die)
        {
            write_status(philo, DIED);
            exit(1);
        }
        sem_post(philo->sem_death);
        usleep(100);
    }
    return (NULL);
}


void wait_for_simulation_to_end(t_philo *philo)
{
    int status;
    int exit_count;
    int i;

    exit_count = 0;
    
    while(exit_count < philo->philo_nbr)
    {
        waitpid(-1, &status, 0);
        //status = 1 then a philo died 
        // if (status == 1)
        if ((status >> 8)== 1)
        {
            i = -1;
            while(++i < philo->philo_nbr)
                kill(philo->pids[i], SIGKILL); //force kill all the process
            break;
        }
        else
            exit_count++;
        
    }
    //Clean the semaphore and the memory

    //Close the semaphores in the parent process
    sem_close(philo->sem_forks);
    sem_close(philo->sem_write);
    sem_close(philo->sem_meal_check);
    sem_close(philo->sem_death);

    // Unlink the semaphore named to remove from the system
    sem_unlink("/forks");
    sem_unlink("/write");
    sem_unlink("/meal_check");
    sem_unlink("/death");
}

int simulation(t_philo *philo)
{
    int i;

    i = -1;
    
    philo->start_simulation = gettime();
    while(++i < philo->philo_nbr)
    {
        philo->pids[i] = fork();
        if (philo->pids[i] < 0)
            return (printf("Error: fork failed\n"), 1);
        if (philo->pids[i] == 0)
        {
            // philo->start_simulation = gettime();
            //now we are in the child process
            start_philosopher(philo, i);
            exit(0);
        }
        usleep(1000); // delay to avoid collision at start        
    }
    //monitor meals or death
    wait_for_simulation_to_end(philo);
    return (0);
}