/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:47 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/24 20:57:21 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SUCCESS 0
#define	FAIL 1

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdatomic.h>

typedef struct s_program
{
	int					num_philos;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				time_start;
	int					meals_required;
	atomic_int			stop_sim;
	pthread_mutex_t		*mtx_forks;
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_meal;
	pthread_mutex_t		mtx_stop;
	struct s_philo		*philos;
}	t_program;

typedef struct s_philo
{
	t_program			*program;
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*fork[2];
	size_t				time_last_meal;
	atomic_int			meals_eaten;
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_philo(const char *str);
size_t	get_time(void);
int		ft_print(t_philo *philo, const char *message);
void	safe_usleep(t_philo *philo, size_t mls);
int		is_dead(t_philo *philo);

int		validate_argc(int argc);
int		validate_input(int argc, char **argv);
int		is_valid_number(const char *str);

int		init_program(int argc, char **argv, t_program *program);
int		simulate(t_program *program);
void	*routine(void *arg);
void	*monitor(void *arg);

void	destroy_partial_forks(t_program *program, int created);
void	delete_program(t_program *program);
void	destroy_forks(t_program *program);
