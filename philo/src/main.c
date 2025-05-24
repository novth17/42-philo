/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 22:53:07 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (validate_argc(argc) == FAIL)
		return (FAIL);
	if (validate_input(argc, argv))
		return (FAIL);
	if (init_program(argc, argv, &program) == FAIL)
		return (FAIL);
	if (simulate(&program) == FAIL)
		return (FAIL);
	delete_program(&program);
	return (SUCCESS);
}
