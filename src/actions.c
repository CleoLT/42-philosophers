/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:16 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/30 17:18:45 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long long	time;

	time = get_time() - philo->rules->t_start;
	pthread_mutex_lock(&philo->rules->print);
	if (!check_death_flag(philo))
		printf("%06lld\t%d\t%s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(&philo->rules->print);
}

void	ft_wait(t_philo *philo, int wait)
{
	long long	time;

	time = get_time();
	while (!check_death_flag(philo))
	{
		if (get_time() - time >= wait)
			break ;
		usleep(150);
	}
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_wait(philo, philo->rules->t_sleep);
}

void	ft_eating(t_philo *philo)
{
	int	first_fork;
	int	sec_fork;

	init_forks_id(&first_fork, &sec_fork, philo->id, philo->rules->nb_philo);
	pthread_mutex_lock(&philo->rules->forks[sec_fork]);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->rules->forks[first_fork]);
	print_action(philo, FORK);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->rules->last_meal);
	philo->nb_meal++;
	philo->is_eating = 1;
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&philo->rules->last_meal);
	ft_wait(philo, philo->rules->t_eat);
	pthread_mutex_lock(&philo->rules->last_meal);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->rules->last_meal);
	pthread_mutex_unlock(&philo->rules->forks[sec_fork]);
	pthread_mutex_unlock(&philo->rules->forks[first_fork]);
}
