/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:22:58 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 14:47:20 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		destroy_forks(t_program *program);
static void	free_philos(t_program *program);

void	delete_program(t_program *program)
{
	if (!program)
		return ;
	destroy_forks(program);
	pthread_mutex_destroy(&program->mtx_print);
	pthread_mutex_destroy(&program->mtx_meal);
	pthread_mutex_destroy(&program->mtx_stop);
	free_philos(program);
	program->num_philos = 0;
}

void	destroy_forks(t_program *program)
{
	int	i;

	i = 0;
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

static void	free_philos(t_program *program)
{
	if (program->philos)
	{
		free(program->philos);
		program->philos = NULL;
	}
}

void	destroy_partial_forks(t_program *program, int created)
{
	while (--created >= 0)
		pthread_mutex_destroy(&program->mtx_forks[created]);
	free(program->mtx_forks);
	program->mtx_forks = NULL;
}
