/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/14 17:29:55 by cle-tron         ###   ########.fr       */
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

//UTILS
int			ft_atoi(const char *str);
int 		ft_isdigit(int c);
long long	get_time(void);

//EXEC
void	exec_philo(t_rules *rules);

#endif
