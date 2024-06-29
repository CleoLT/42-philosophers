/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/29 16:34:40 by cle-tron         ###   ########.fr       */
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
void	init_forks_id(int *first, int *sec, int id, int size);

//UTILS
int			ft_atoi(const char *str);
int 		ft_isdigit(int c);
long long	get_time(void);

//EXEC
void	exec_philo(t_rules *rules);
void	print_action(t_philo *philo, char *action);

//FINISH
void	*check_end(void *data);

#endif
