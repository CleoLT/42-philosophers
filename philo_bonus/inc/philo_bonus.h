/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 13:51:53 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

# include "structures_bonus.h"

//INIT
void		init_rules(char **argv, t_rules *rules);

//UTILS
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time(void);

//EXEC
void		exec_philo(t_rules *rules);

//ACTIONS
void		print_action(t_philo *philo, char *action);
void		ft_sleep(t_philo *philo);
void		ft_eating(t_philo *philo);

//CHECK_END
void		*check_end(void *data);

#endif
