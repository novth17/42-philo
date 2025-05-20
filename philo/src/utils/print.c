/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:17:41 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/20 21:18:16 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->mtx_stop);
	if (philo->program->stop_sim == 1)
	{
		pthread_mutex_unlock(&philo->program->mtx_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->mtx_stop);
	return (0);
}

int	ft_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->program->mtx_print);
	if (philo->program->stop_sim)
		return (FAIL);
	printf("%zu Philosopher %d %s\n",
		get_time() - philo->program->time_start,
		philo->id, message);
	pthread_mutex_unlock(&philo->program->mtx_print);
	return (SUCCESS);
}
