/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:40:08 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/03 17:07:34 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_forks_id(int *first, int *sec, int id, int size)
{
	if (id == 0)
		*first = size - 1 ;
	else if (id % 2 == 0)
		*first = id - 1;
	else if (id % 2 != 0)
		*first = id;
	if (id % 2 != 0)
		*sec = id - 1;
	else
		*sec = id;
}

void	init_index(int **index, int size)
{
	int	i;
	int	value;

	*index = malloc(sizeof(int ) * size);
	if (!*index)
		return ;
	i = 0;
	value = 0;
	while (value < size)
	{
		(*index)[i] = value;
		i++;
		value += 2;
	}
	value = 1;
	while (i < size)
	{
		(*index)[i] = value;
		i++;
		value += 2;
	}
}
/*	i = 0;
	while (i <size)
		printf("%d ", (*index)[i++] + 1);
	printf("\n");
*/

/*
pthread_mutex_t	*init_forks(t_rules *rules)
{
	int				i;
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!mutex)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL))
			return (NULL);
		i++;
	}
	return (mutex);
}
*/

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
		printf("%lld t_lastmeal init\n", philo[i].t_last_meal);
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
	rules->death =  sem_open("/death", O_CREAT, 0700, 1);
	rules->last_meal = sem_open("/last_meal", O_CREAT, 0700, 1);
	if (rules->forks == SEM_FAILED || rules->print == SEM_FAILED || \
		rules->death == SEM_FAILED || rules->last_meal == SEM_FAILED)
		return ;
	rules->death_flag = 0;
}
