/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:47 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/14 18:12:17 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SUCCESS 0
#define	FAIL 1

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_program
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_required; // optional, if argc == 6
	pthread_mutex_t  *forks_on_table;
	struct s_philo *philos;
}	t_program;

// allocate an array based on ammount of philo
//

typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread;
	pthread_mutex_t		*fork[2];
	//last meal time
	//meals eaten
}	t_philo;

//utils
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_philo(const char *str);

//functions
int		validate_argc(int argc);
int		validate_input(int argc, char **argv);
int		is_valid_number(const char *str);
int		init(int argc, char **argv, t_program *program);
void	delete_program(t_program *program);



