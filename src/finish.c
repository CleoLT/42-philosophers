/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/28 18:17:28 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	check_nb_meal(t_philo *philo)
{
	if (philo->rules->nb_eat == -1)
		return(0);
	return (1);
}

int	check_last_meal(t_philo *philo)
{
//	long long time_diff;

printf("%d  \n\n ", philo->id);
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff >= philo->rules->t_die)
	{	
		print_action(philo, DEATH);
		pthread_mutex_lock(&philo->rules->death);
		philo->rules->death_flag = 1;
		pthread_mutex_unlock(&philo->rules->death);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
	//	printf("%d  \n\n ", rules->philo[i].id);

		//if (check_last_meal(rules->philo[i]))
		//	return (1);
		i++;
	}
	return (0);
}

void	*check_finished(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("%d  \n\n ", philo[1].id);

	while (1)
		if (check_death(philo) || check_nb_meal(philo))
			return(NULL) ;
//	return (NULL);
}*/

int	check_nb_meal(t_rules *rules)
{
	if (rules->nb_eat == -1)
		return(0);
	return (1);
}

int	check_last_meal(t_philo *philo)
{
	long long time_diff;

//printf("%d  \n\n ", rules->philo[0].id);
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff >= philo->rules->t_die)
	{	
		print_action(philo, DEATH);
		pthread_mutex_lock(&philo->rules->death);
		philo->rules->death_flag = 1;
		pthread_mutex_unlock(&philo->rules->death);
		return (1);
	}
	return (0);
}

int	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
	//	printf("%d  \n\n ", rules->philo[i].id);

		if (check_last_meal(&rules->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*check_finished(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
//	int i = 0;
//	printf("%d nbphilo\n", rules->nb_philo);
//	while (i < rules->nb_philo)
//	{

//	printf("%d\n", rules->philo[i].id);
//	i++;
//}
	while (1)
		if (check_death(rules) || check_nb_meal(rules))
			return(NULL) ;
//	return (NULL);
}
