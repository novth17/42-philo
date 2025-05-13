/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:33:13 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/13 15:59:58 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi_philo(const char *str, int *out)
{
	long	result;
	int		digit;

	result = 0;
	if (!str || !str[0])
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		return (0);
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (INT_MAX - digit) / 10)
			return (0);
		result = result * 10 + digit;
		str++;
	}
	if (*str != '\0' || result == 0)
		return (0);
	*out = (int)result;
	return (1);
}

