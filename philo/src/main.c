/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 14:48:09 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_program(t_program *program)
{
	pthread_mutex_lock(&program->mtx_print);
	printf("Number of philosophers: %d\n", program->num_philos);
	printf("Time to die: %zu ms\n", program->time_die);
	printf("Time to eat: %zu ms\n", program->time_eat);
	printf("Time to sleep: %zu ms\n", program->time_sleep);
	if (program->meals_required == -1)
		printf("Meals required: (not set)\n");
	else
		printf("Meals required: %d\n", program->meals_required);
	pthread_mutex_unlock(&program->mtx_print);
}

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
	print_program(&program);
	delete_program(&program);
	return (SUCCESS);
}
