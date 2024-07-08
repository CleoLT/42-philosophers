/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:40:08 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 15:53:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philosophers(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i;
		philo[i].t_last_meal = get_time();
		philo[i].nb_meal = 0;
		philo[i].rules = rules;
		philo[i].is_eating = 0;
		i++;
	}
	return (philo);
}

void	init_rules(char **argv, t_rules *rules)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->nb_eat = ft_atoi(argv[5]);
	else
		rules->nb_eat = -1;
	rules->t_start = get_time();
	rules->philo = init_philosophers(rules);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/last_meal");
	rules->forks = sem_open("/forks", O_CREAT, 0700, rules->nb_philo);
	rules->print = sem_open("/print", O_CREAT, 0700, 1);
	rules->last_meal = sem_open("/last_meal", O_CREAT, 0700, 1);
	if (rules->forks == SEM_FAILED || rules->print == SEM_FAILED || \
		rules->last_meal == SEM_FAILED)
		return ;
}
