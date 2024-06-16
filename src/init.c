/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:40:08 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/16 20:51:13 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//PAIR
void	even_index(int **index, int size)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (i < size)
	{
		(*index)[i] = value;
		i+= 2;
		value += 2;
	}
	i = 1;
	if (size%4 == 0)
		value = (size-1) / 2 + 2;
	else
		value = size /2;
	while (i <size)
	{
		(*index)[i] = value%size;
		i+= 2;
		value += 2;
	}
}

//IMPAIR
void	odd_index(int **index, int size)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while ( value < size )
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

void	init_index(int **index, int size)
{
	*index = malloc(sizeof(int ) * size);
	if (!*index)
		return ;
	if ( size%2 != 0 || size < 7)
		odd_index(index, size);
	else
		even_index(index, size);
//	int i = 0;
//	while (i <size)
//		printf("%d ", (*index)[i++]);
}

pthread_mutex_t *init_forks(t_rules *rules)
{
	int	i;
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!mutex)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}


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
		philo[i].t_last_meal = 0;
		philo[i].nb_meal = 0;
		philo[i].rules = rules;
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
	rules->forks = init_forks(rules);
	rules->death_flag = 0;
}
