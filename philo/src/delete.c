/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:22:58 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:14 by hiennguy         ###   ########.fr       */
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

static void	free_forks_on_table(t_program *program)
{
	int	i = 0;

	if (program->forks_on_table)
	{
		while (i < program->num_philos)
		{
			pthread_mutex_destroy(&program->forks_on_table[i]);
			i++;
		}
		free(program->forks_on_table);
		program->forks_on_table = NULL;
	}
}


void	delete_program(t_program *program)
{
	if (!program)
		return;
	free_forks_on_table(program);
	free_philos(program);
	program->num_philos = 0;
}

