/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:12 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/16 17:27:35 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_program(int argc, char **argv, t_program *program)
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
	program->mtx_forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->mtx_forks)
		return (FAIL);
	while(i < program->num_philos)
	{
		if (pthread_mutex_init(&program->mtx_forks[i], NULL) != 0)
		{
			free_partial_forks(program, i);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_philos(t_program *program)
{
	int	i;

	i = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (FAIL);
	while (i < program->num_philos)
	{
		program->philos[i].philo_id = i + 1;
		program->philos[i].fork[0] = &program->mtx_forks[i];
		program->philos[i].fork[1] = &program->mtx_forks[(i + 1) % program->num_philos];
		i++;
	}
	return (SUCCESS);
}

static void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	//usleep(1000);
	printf("Philosopher %d started\n", philo->philo_id);
	return (NULL);
}

static void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}

static int	create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
					&routine, &program->philos[i]) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	init(int argc, char **argv, t_program *program)
{
	if (init_program(argc, argv, program) == FAIL)
		return (FAIL);
	if (init_philos(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	if (create_threads(program) == FAIL)
	{
		delete_program(program);
		return (FAIL);
	}
	join_threads(program);
	return (SUCCESS);
}
