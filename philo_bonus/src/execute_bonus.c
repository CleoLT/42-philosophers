/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 15:21:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_and_close_sem(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		waitpid(-1, &status, 0);
	//	if (WEXITSTATUS(status) == 1)
		if (status != 0)
		{
			i = 0;
			while (i < philo->rules->nb_philo)
				kill(philo->rules->philo[i++].pid, SIGKILL);
			break;
		}
		i++;
	}
	if (sem_close(philo->rules->print) == -1 || \
		sem_close(philo->rules->last_meal) == -1 || \
		sem_close(philo->rules->forks) == -1)
		return ;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/last_meal");	
}

void	philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->end_check, NULL, check_end, philo))
		return ;
	while (1)
	{
		ft_eating(philo);
		ft_sleep(philo);
		print_action(philo, THINK);
		usleep(500);
	}
	if (pthread_join(philo->end_check, NULL))
		return ;
}

void	exec_philo(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->nb_philo == 1)
	{
		print_action(rules->philo, FORK);
		usleep(rules->t_die * 1000);
		print_action(rules->philo, DEATH);
		return ;
	}
	while (i < rules->nb_philo)
	{
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == -1)
			return ;
		if (rules->philo[i].pid == 0)
			philo_routine(&rules->philo[i]);
		usleep(500);
		i++;
	}
	kill_and_close_sem(rules->philo);
}
