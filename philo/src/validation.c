/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:10:25 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/19 16:27:30 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	is_valid_number(const char *str)
{
	long	result;

	result = 0;
	if (!str || !str[0])
		return (0);
	if (*str == '+' || *str == '-')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (0);
		str++;
	}
	if (*str != '\0' || result == 0)
		return (0);
	return (1);
}

int	validate_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Invalid argument count: must provide 4 or 5 arguments.\n", 2);
		return (FAIL);
	}
	return (SUCCESS);
}

int	validate_input(int argc, char **argv)
{
	int	i = 1;

	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			ft_putstr_fd("Error: Invalid number: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\n", 2);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

