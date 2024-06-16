/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/16 20:41:57 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# include "structures.h"

//INIT
void	init_rules(char **argv, t_rules *rules);
void	init_index(int **index, int size);

//UTILS
int			ft_atoi(const char *str);
int 		ft_isdigit(int c);
long long	get_time(void);

//EXEC
void	exec_philo(t_rules *rules);

#endif
