/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:35:10 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 14:48:38 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_program *program);
static int	join_threads(t_program *program);
static int	monitor_threads(t_program *program);

/*
Create all philosopher threads.
Create the monitor thread.
Join all philosopher threads.
Join the monitor thread.
Clean up memory, destroy mutexes, etc.
Exit main.
*/

int	simulate(t_program *program)
{
	if (create_threads(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	/*This waits for all philosopher threads (and maybe the monitor) to finish.
		Main thread pauses here until all others are done.*/
	if (monitor_threads(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
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

static int	monitor_threads(t_program *program)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, program) != 0)
	{
		ft_putstr_fd("Monitor thread creation failed!\n", 2);
		return (FAIL);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		ft_putstr_fd("Monitor thread join failed!\n", 2);
		return (FAIL);
	}
	return (SUCCESS);
}

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

