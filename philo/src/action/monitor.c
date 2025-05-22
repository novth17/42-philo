/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:24:56 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/22 17:59:55 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
	int			full_philo_count;

	while (1)
	{
		i = 0;
		full_philo_count = 0;
		while (i < program->num_philos)
		{
			pthread_mutex_lock(&program->mtx_meal);
			now = get_time();
			if (now - program->philos[i].time_last_meal > program->time_die)
			{
				ft_print(program->philos, "is dead");
				pthread_mutex_lock(&program->mtx_stop);
				program->stop_sim = 1;
				pthread_mutex_unlock(&program->mtx_stop);

				pthread_mutex_unlock(&program->mtx_meal);
				return (NULL); // EXIT ERALY WHEN A PHILO DIE
			}

			if (program->philos[i].meals_eaten >= program->meals_required)
					full_philo_count++;
			pthread_mutex_unlock(&program->mtx_meal);
			i++;
		}
		if (program->meals_required != -1 && full_philo_count == program->num_philos)
		{
			pthread_mutex_lock(&program->mtx_stop);
			program->stop_sim = 1;
			pthread_mutex_unlock(&program->mtx_stop);
			break;
		}
		usleep(1000);
	}
	return (NULL);
}

int	monitor_threads(t_program *program)
{
	pthread_t monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, program) != 0)
	{
		ft_putstr_fd("Monitor thread creation failed!\n", 2);
		return (FAIL);
	}
	return (SUCCESS);
}
