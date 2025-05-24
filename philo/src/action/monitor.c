/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:24:56 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 20:41:44 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	someone_is_dead(t_program *program);
static int	kill_philo(t_program *program, int i, long now);
static int	check_all_full(t_program *program);
static void	stop_simulation(t_program *program);

void	*monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (someone_is_dead(program))
			return (NULL);
		if (program->meals_required != -1 && check_all_full(program))
		{
			stop_simulation(program);
			break ;
		}
	}
	usleep(100);
	return (NULL);
}

static int	someone_is_dead(t_program *program)
{
	int		i;
	long	now;

	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->mtx_meal);
		now = get_time();
		if (kill_philo(program, i, now))
		{
			pthread_mutex_unlock(&program->mtx_meal);
			return (1);
		}
		pthread_mutex_unlock(&program->mtx_meal);
		i++;
	}
	return (0);
}

static int	kill_philo(t_program *program, int i, long now)
{
	if (now - program->philos[i].time_last_meal > program->time_die)
	{
		ft_print(&program->philos[i], "died");
		stop_simulation(program);
		return (1);
	}
	return (0);
}

static int	check_all_full(t_program *program)
{
	int	i;
	int	full_philo_count;

	full_philo_count = 0;
	i = 0;
	while (i < program->num_philos)
	{
		pthread_mutex_lock(&program->mtx_meal);
		if (program->philos[i].meals_eaten >= program->meals_required)
			full_philo_count++;
		pthread_mutex_unlock(&program->mtx_meal);
		i++;
	}
	return (full_philo_count == program->num_philos);
}

static void	stop_simulation(t_program *program)
{
	pthread_mutex_lock(&program->mtx_stop);
	program->stop_sim = 1;
	pthread_mutex_unlock(&program->mtx_stop);
}
