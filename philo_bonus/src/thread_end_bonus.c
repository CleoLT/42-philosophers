/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_end_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 15:55:09 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_philo *philo)
{
	long long	time_diff;

	if (sem_wait(philo->rules->last_meal) == -1)
		return ;
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff > philo->rules->t_die && philo->is_eating == 0)
	{
		print_action(philo, DEATH);
		sem_wait(philo->rules->print);
		if (sem_post(philo->rules->last_meal) == -1)
			return ;
		exit(1);
	}
	if (philo->rules->nb_eat != -1 && philo->nb_meal >= philo->rules->nb_eat)
	{
		if (sem_post(philo->rules->last_meal) == -1)
			return ;
		exit(0);
	}
	if (sem_post(philo->rules->last_meal) == -1)
		return ;
}

void	*check_end(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		usleep(300);
		check_death(philo);
	}
}
