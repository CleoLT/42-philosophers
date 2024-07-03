/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:10 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/03 16:24:04 by cle-tron         ###   ########.fr       */
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
# include <sys/types.h>
# include <unistd.h>

# include "structures_bonus.h"

//INIT
void		init_rules(char **argv, t_rules *rules);
void		init_index(int **index, int size);
void		init_forks_id(int *first, int *sec, int id, int size);

//UTILS
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time(void);

//EXEC
void		exec_philo(t_rules *rules);
int			check_death_flag(t_philo *philo);

//ACTIONS
void		print_action(t_philo *philo, char *action);
void		ft_sleep(t_philo *philo);
void		ft_eating(t_philo *philo);

//CHECK_END
void		*check_end(void *data);

#endif
