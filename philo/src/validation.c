/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:10:25 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/13 17:01:45 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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
	int		i;
	int		num;

	i = 1;
	while (i < argc)
	{
		if(!ft_atoi_philo(argv[i], &num))
		{
			ft_putstr_fd("Error: Invalid argument\n", 2);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}
