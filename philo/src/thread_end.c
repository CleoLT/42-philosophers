/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/02 11:23:54 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_meal(t_rules *rules)
{
	int	i;
	int	count;

	if (rules->nb_eat == -1)
		return (0);
	i = 0;
	count = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->last_meal);
		if (rules->philo[i].nb_meal >= rules->nb_eat)
			count++;
		pthread_mutex_unlock(&rules->last_meal);
		i++;
	}
	if (count >= rules->nb_philo)
	{
		pthread_mutex_lock(&rules->death);
		rules->death_flag = 1;
		pthread_mutex_unlock(&rules->death);
		return (1);
	}
	usleep(100);
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	long long	time_diff;

	pthread_mutex_lock(&philo->rules->last_meal);
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff > philo->rules->t_die && philo->is_eating == 0)
	{
		print_action(philo, DEATH);
		pthread_mutex_lock(&philo->rules->death);
		philo->rules->death_flag = 1;
		pthread_mutex_unlock(&philo->rules->death);
		pthread_mutex_unlock(&philo->rules->last_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->last_meal);
	return (0);
}

int	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (check_last_meal(&rules->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*check_end(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
	while (1)
		if (check_death(rules) || check_nb_meal(rules))
			return (NULL);
}
