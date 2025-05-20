/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:12 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/20 21:15:17 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_program *program);
static int	init_philos(t_program *program);
static int	init_mtx(t_program *program);

int	init_program(int argc, char **argv, t_program *program)
{
	int	i;

	i = 0;
	program->num_philos = ft_atoi_philo(argv[1]);
	program->time_die = ft_atoi_philo(argv[2]);
	program->time_eat = ft_atoi_philo(argv[3]);
	program->time_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		program->meals_required = ft_atoi_philo(argv[5]);
	else
		program->meals_required = -1;
	program->time_start = 0;
	program->stop_sim = 0;
	if (init_forks(program) == FAIL)
		return (FAIL);
	if (init_mtx(program) == FAIL)
		return (FAIL);
	if (init_philos(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	init_forks(t_program *program)
{
	int	i;

	i = 0;
	program->mtx_forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->mtx_forks)
		return (FAIL);
	while(i < program->num_philos)
	{
		if (pthread_mutex_init(&program->mtx_forks[i], NULL) != 0)
		{
			destroy_partial_forks(program, i);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_mtx(t_program *program)
{
	if (pthread_mutex_init(&program->mtx_meal, NULL) != 0
		|| pthread_mutex_init(&program->mtx_print, NULL) != 0
		|| pthread_mutex_init(&program->mtx_stop, NULL) != 0)
	{
		destroy_forks(program);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	init_philos(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
	{
		ft_putstr_fd("malloc failed", 2);
		return (FAIL);
	}
	while (i < program->num_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].fork[0] = &program->mtx_forks[i];
		program->philos[i].fork[1] = &program->mtx_forks[(i + 1) % program->num_philos];
		program->philos[i].meals_eaten = 0;
		program->philos[i].time_last_meal = 0;
		program->philos[i].program = program;
		i++;
	}
	return (SUCCESS);
}
