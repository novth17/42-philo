/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:47 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/13 16:44:39 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SUCCESS 0
#define	FAIL 1

typedef struct s_program
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_required; // optional, if argc == 6
	int	has_meals_required; // 1 if provided, 0 otherwise
}	t_program;



//utils
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_philo(const char *str, int *out);

//functions
int		validate_argc(int argc);
int		validate_input(int argc, char **argv);

