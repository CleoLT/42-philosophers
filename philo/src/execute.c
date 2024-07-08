/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/02 13:58:16 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_philo *philo)
{
	int	value;

	value = 0;
	if (pthread_mutex_lock(&philo->rules->death))
		return (-1);
	if (philo->rules->death_flag == 1)
		value = 1;
	if (pthread_mutex_unlock(&philo->rules->death))
		return (-1);
	return (value);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!check_death_flag(philo))
	{
		ft_eating(philo);
		ft_sleep(philo);
		print_action(philo, THINK);
		usleep(500);
	}
	return (NULL);
}

void	join_and_destroy(int *idx, t_rules *rules)
{
	int	i;

	if (pthread_join(rules->finish, NULL))
		return ;
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[idx[i]].thread, NULL))
			return ;
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_destroy(&rules->forks[idx[i]]))
			return ;
		i++;
	}
	if (pthread_mutex_destroy(&rules->print) || \
		pthread_mutex_destroy(&rules->death) || \
		pthread_mutex_destroy(&rules->last_meal))
		return ;
	if (idx)
		free(idx);
}

void	exec_philo(t_rules *rules)
{
	int	i;
	int	*idx;

	i = 0;
	idx = NULL;
	if (rules->nb_philo == 1)
	{
		print_action(rules->philo, FORK);
		usleep(rules->t_die * 1000);
		print_action(rules->philo, DEATH);
		return ;
	}
	init_index(&idx, rules->nb_philo);
	if (pthread_create(&rules->finish, NULL, check_end, rules))
		return ;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[idx[i]].thread, NULL, philo_routine, \
												&rules->philo[idx[i]]))
			return ;
		usleep(100);
		i++;
	}
	join_and_destroy(idx, rules);
}
