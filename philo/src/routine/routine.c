/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:15 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/20 21:18:05 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
- think
- take left fork (mutex lock)
- take right fork (mutex lock)
- eat (update last_meal, print, sleep)
- release forks (mutex unlock)
- sleep
- repeat unless someone dies or eats enough
 */
static int	safe_usleep(t_philo *philo, size_t mls)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < mls)
	{
		if (philo && philo->program->stop_sim == 1)
			break;
		usleep(1000);
	}
	return (SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	if (ft_print(philo, "is sleeping") == FAIL)
		return (FAIL);
	safe_usleep(philo, philo->program->time_sleep);
	return (SUCCESS);
}


static int	ft_think(t_philo *philo)
{
	if (ft_print(philo, "is thinking") == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	if (ft_print(philo, "has taken a fork") == FAIL)
		return (FAIL);
	if (philo->program->num_philos == 1)
	{
		pthread_mutex_unlock(philo->fork[0]);
		//should it die and stop sim here???
		return (FAIL);
	}
	pthread_mutex_lock(philo->fork[1]);
	if (ft_print(philo, "has taken a fork") == FAIL)
		return (FAIL);

	return (SUCCESS);
}


static int	ft_eat(t_philo *philo)
{
	t_program *program = philo->program;

	if (ft_print(philo, "is eating") == FAIL)
		return (FAIL);

	pthread_mutex_lock(&program->mtx_meal);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&program->mtx_meal);

	//The philosopher is actively eating, and we simulate the duration of
	//eating by making the thread sleep.
	safe_usleep(philo, program->time_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
	return (SUCCESS);

}
/*
This line casts the void * argument passed to the thread function into
a t_philo * pointer, so that the thread can access the philosopher’s data.
*/
void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	//delay time eat /2

	if (philo->id % 2 == 0)
		safe_usleep(philo, philo->program->time_eat / 2);
	while (1)
	{
		if (ft_take_fork(philo) == FAIL)
			break;
		if (ft_eat(philo) == FAIL)
			break;
		if (ft_sleep(philo) == FAIL)
			break;
		if (ft_think(philo) == FAIL)
			break;
		if (philo->program->stop_sim == 1)
			break;
	}
	printf("Philo %d meals: %d\n", philo->id, philo->meals_eaten);
	return (NULL);
}
