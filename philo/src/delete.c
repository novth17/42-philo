/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:22:58 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/16 16:42:13 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_program *program)
{
	if (program->philos)
	{
		free(program->philos);
		program->philos = NULL;
	}
}

void	free_partial_forks(t_program *program, int created)
{
	while (--created >= 0)
		pthread_mutex_destroy(&program->mtx_forks[created]);
	free(program->mtx_forks);
	program->mtx_forks = NULL;
}

static void	free_mtx_forks(t_program *program)
{
	int	i = 0;

	if (program->mtx_forks)
	{
		while (i < program->num_philos)
		{
			pthread_mutex_destroy(&program->mtx_forks[i]);
			i++;
		}
		free(program->mtx_forks);
		program->mtx_forks = NULL;
	}
}


void	delete_program(t_program *program)
{
	if (!program)
		return;
	free_mtx_forks(program);
	free_philos(program);
	program->num_philos = 0;
}

