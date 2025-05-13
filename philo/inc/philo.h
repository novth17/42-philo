/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:30:47 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/13 16:08:25 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SUCCESS 0
#define	FAIL 1

//utils
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_philo(const char *str, int *out);

//functions
int		validate_argc(int argc);
int		validate_input(int argc, char **argv);

