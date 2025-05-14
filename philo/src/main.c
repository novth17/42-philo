/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:08:52 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_program(t_program *program)
{
	printf("Number of philosophers: %d\n", program->num_philos);
	printf("Time to die: %d ms\n", program->time_to_die);
	printf("Time to eat: %d ms\n", program->time_to_eat);
	printf("Time to sleep: %d ms\n", program->time_to_sleep);
	if (program->meals_required == -1)
		printf("Meals required: (not set)\n");
	else
		printf("Meals required: %d\n", program->meals_required);
}


int	main(int argc, char **argv)
{
	t_program	program;
	if (validate_argc(argc) == FAIL)
		return (FAIL);
	if (validate_input(argc, argv))
		return (FAIL);
	if (init(argc, argv, &program) == FAIL)
		return (FAIL);
	print_program(&program);
	return (SUCCESS);
}


