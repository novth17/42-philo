/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:17:41 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 16:48:38 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->program->mtx_print);
	if (philo->program->stop_sim)
	{
		pthread_mutex_unlock(&philo->program->mtx_print);
		return (FAIL);
	}
	printf("%zu %d %s\n",
			get_time() - philo->program->time_start,
			philo->id,
			message);
	pthread_mutex_unlock(&philo->program->mtx_print);
	return (SUCCESS);
}

