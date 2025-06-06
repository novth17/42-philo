/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:26:19 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/25 19:16:10 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int	ft_atoi_philo(const char *str)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
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

void	safe_usleep(t_philo *philo, size_t mls)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < mls)
	{
		if (philo && philo->program->stop_sim == 1)
			break ;
		usleep(1000);
	}
}
