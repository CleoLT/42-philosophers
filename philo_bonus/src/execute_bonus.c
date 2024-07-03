/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/03 18:02:11 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
void	kill_and_close_sem(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		kill(rules->philo[i].pid, SIGKILL);
		i++;
	}
	if (sem_close(rules->print) == -1 || sem_close(rules->death) ==-1 || \
		sem_close(rules->last_meal) == -1 || sem_close(rules->forks) == -1)
		return ;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/last_meal");	
}

int	check_death_flag(t_philo *philo)
{
	int	value;

	value = 0;
	if (sem_wait(philo->rules->death) == -1)
		return (-1);
	if (philo->rules->death_flag == 1)
		value = 1;
	if (sem_post(philo->rules->death) == -1)
		return (-1);
	return (value);
}

void	philo_routine(t_philo *philo)
{
/*	if (pthread_create(&philo->end_check, NULL, check_end, philo->rules) || \
		pthread_detach(philo->end_check))
		return ;
*/
while (!check_death_flag(philo))
	{
		ft_eating(philo);
		ft_sleep(philo);
		print_action(philo, THINK);
		usleep(500);
	}
//	printf("JJJJJJJ");
//	if (pthread_join(philo->end_check, NULL))
//		return ;
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
	if (pthread_create(&rules->end_check, NULL, check_end, rules))
		return ;
	while (i < rules->nb_philo)
	{
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == -1)
			return ;
		if (rules->philo[i].pid == 0)
			philo_routine(&rules->philo[i]);
		usleep(100);
		i++;
	}
	if (pthread_join(rules->end_check, NULL))
		return ;
	kill_and_close_sem(rules);
}
