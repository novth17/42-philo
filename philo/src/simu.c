/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:35:10 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/20 21:19:11 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_program *program);
static int	join_threads(t_program *program);

int	simulate(t_program *program)
{
	if (create_threads(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	//monitor_threads(program)
	if (join_threads(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	create_threads(t_program *program)
{
	int	i;

	i = 0;
	program->time_start = get_time();
	while (i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &routine,
				&program->philos[i]) != 0)
		{
			ft_putstr_fd("Thread creation failed!\n", 2);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

// What monitor_thread() should do:
	// Loop forever (or until someone dies)
	// For each philosopher:
	// Lock mtx_meals
	// Check time since last_meal
	// If too much time passed → log death and set stop_sim
	// Unlock mtx_meals
	// Sleep a little to avoid eating your CPU

void	*monitor(void *arg)
{
	t_program	*program = (t_program *)arg;
	int			i;
	size_t		now;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->mtx_meal);
		now = get_time();

		pthread_mutex_unlock(&program->mtx_meal);
		i++;
	}
	printf("Monitor thread created\n");
	return (NULL);
}


// static int	monitor_threads(t_program *program)
// {
// 	pthread_t monitor_thread;

// 	if (pthread_create(&monitor_thread, NULL, &monitor, program) != 0)
// 	{
// 		ft_putstr_fd("Monitor thread creation failed!\n", 2);
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

static int	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			ft_putstr_fd("Thread join failed!\n", 2);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

