/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:12 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 22:16:07 by hiennguy         ###   ########.fr       */
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
	program->time_start = get_time();
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
	while (i < program->num_philos)
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

static void	assign_forks(t_program *program, t_philo *philo, int i)
{
	int	left;
	int	right;

	left = i;
	right = (i + 1) % program->num_philos;
	if (i % 2 == 0)
	{
		philo->fork[0] = &program->mtx_forks[left];
		philo->fork[1] = &program->mtx_forks[right];
	}
	else
	{
		philo->fork[1] = &program->mtx_forks[left];
		philo->fork[0] = &program->mtx_forks[right];
	}
}

static int	init_philos(t_program *program)
{
	int		i;
	t_philo	*philo;

	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
	{
		ft_putstr_fd("malloc failed\n", 2);
		return (FAIL);
	}
	i = 0;
	while (i < program->num_philos)
	{
		philo = &program->philos[i];
		philo->id = i + 1;
		assign_forks(program, philo, i);
		philo->meals_eaten = 0;
		philo->time_last_meal = program->time_start;
		philo->program = program;
		i++;
	}
	return (SUCCESS);
}
