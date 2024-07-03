/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:16 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/03 17:06:23 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_philo *philo, char *action)
{
	long long	time;

	time = get_time() - philo->rules->t_start;
	if (sem_wait(philo->rules->print) == -1)
		return ;
	if (!check_death_flag(philo))
		printf("%06lld\t%d\t%s\n", time, philo->id + 1, action);
	if (sem_post(philo->rules->print) == -1)
		return ;
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
//	int	first_fork;
//	int	sec_fork;

//	init_forks_id(&first_fork, &sec_fork, philo->id, philo->rules->nb_philo);
	if (sem_wait(philo->rules->forks) == -1)
		return ;
	print_action(philo, FORK);
	if (sem_wait(philo->rules->forks) == -1)
		return ;
	print_action(philo, FORK);
	print_action(philo, EAT);
	if (sem_wait(philo->rules->last_meal) == -1)
		return ;
	philo->nb_meal++;
	philo->is_eating = 1;
	philo->t_last_meal = get_time();
	printf("%lld t_lastmeal actualizacion\n", philo->t_last_meal);
	if (sem_post(philo->rules->last_meal) == -1)
		return ;
	ft_wait(philo, philo->rules->t_eat);
	if (sem_wait(philo->rules->last_meal) == -1)
		return ;
	philo->is_eating = 0;
	if (sem_post(philo->rules->last_meal) == -1 || \
		sem_post(philo->rules->forks) == -1 || \
		sem_post(philo->rules->forks) == -1)
		return ;
}
