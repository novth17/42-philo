/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:15 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/23 17:05:06 by hiennguy         ###   ########.fr       */
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
	{
		pthread_mutex_unlock(philo->fork[0]);
		return (FAIL);
	}
	if (philo->program->num_philos == 1)
	{
		pthread_mutex_unlock(philo->fork[0]);
		return (FAIL);
	}
	pthread_mutex_lock(philo->fork[1]);
	if (ft_print(philo, "has taken a fork") == FAIL)
	{
		pthread_mutex_unlock(philo->fork[1]);
		pthread_mutex_unlock(philo->fork[0]);
		return (FAIL);
	}
	return (SUCCESS);
}


static int	ft_eat(t_philo *philo)
{
	t_program *program = philo->program;


	pthread_mutex_lock(&program->mtx_meal);
	philo->time_last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&program->mtx_meal);

	if (ft_print(philo, "is eating") == FAIL)
	{
		pthread_mutex_unlock(philo->fork[0]);
		pthread_mutex_unlock(philo->fork[1]);
		return (FAIL);
	}
	safe_usleep(philo, program->time_eat);

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
	int first_round = 1;
	t_philo *philo = (t_philo *)arg;
	// const long		delay = philo->program->time_start - now();

	// if (delay > 0)
	// 	safe_usleep(delay, NULL);
	if (philo->id % 2 == 0)
	{
		ft_think(philo);
		safe_usleep(philo, philo->program->time_eat / 2);
	}
	while (1)
	{
		if (philo->id % 2 == 0 && first_round-- <= 0  && ft_think(philo) == FAIL)
			break;
		if (ft_take_fork(philo) == FAIL)
			break;
		if (ft_eat(philo) == FAIL)
			break;
		if (ft_sleep(philo) == FAIL)
			break;
		if (is_dead(philo))
			break;
	}
	// pthread_mutex_lock(&philo->program->mtx_print);
	// printf("Philo %d meals: %d\n", philo->id, philo->meals_eaten);
	// pthread_mutex_unlock(&philo->program->mtx_print);


	return (NULL);
}
