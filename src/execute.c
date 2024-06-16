/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/16 20:51:34 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	printf("%06lld\t%d\t%s\n", get_time() - philo->rules->t_start, philo->id, action);
}

void ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->rules->t_sleep * 1000);
}

void	ft_eating(t_philo *philo)
{
	int	left_fork;

	if (philo->id == 0)
		left_fork = philo->rules->nb_philo;
	else
		left_fork = philo->id - 1;

	pthread_mutex_lock(&philo->rules->forks[philo->id]);
	print_action(philo, FORKR);
	pthread_mutex_lock(&philo->rules->forks[left_fork]);
	print_action(philo, FORKL);
	print_action(philo, EAT);
	philo->t_last_meal = get_time();
	philo->nb_meal++;
//	while (1)
//		if ((get_time() - philo->t_last_meal) >= philo->rules->t_eat)
//			break ;
	usleep(philo->rules->t_eat * 1000);
	ft_sleep(philo);
	pthread_mutex_unlock(&philo->rules->forks[philo->id]);
	pthread_mutex_unlock(&philo->rules->forks[left_fork]);


}



void	*philo_routine(void *data)
{
//	pthread_t	t;
	t_philo		*philo;

//	t = pthread_self();
	philo = (t_philo *)data;
	while (!philo->rules->death_flag)
	{
	//	printf("thread nb: %ld, philo id: %d\n", t, philo->id);
		ft_eating(philo);
		print_action(philo, THINK);
		if (get_time() > (philo->rules->t_start + 1000))
			philo->rules->death_flag = 1;
	}
	return (NULL);
}


void	exec_philo(t_rules *rules)
{
	int i;
	int	*idx;
	
	i = 0;
	idx = NULL;
	init_index(&idx, rules->nb_philo);
	while (i < rules->nb_philo)
	{
	pthread_create(&rules->philo[idx[i]].thread, NULL, philo_routine, &rules->philo[idx[i]]);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[idx[i]].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[idx[i]]);
		i++;
	}
	free(idx);
}
