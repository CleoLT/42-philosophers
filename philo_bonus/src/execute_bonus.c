/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/05 13:44:46 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/*void	kill_and_close_sem(t_rules *rules)
{
	int	i;
	int	status;

	i = 0;

	while (i < rules->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status == 1)
		{
			i = 0;
			printf("HOLABUENOSDIAS\n");
			while (i < rules->nb_philo)
			{
				kill(rules->philo[i].pid, SIGKILL);
				i++;
			}
			break;
		}
		i++;
	}
	if (sem_close(rules->print) == -1 || sem_close(rules->death) ==-1 || \
		sem_close(rules->last_meal) == -1 || sem_close(rules->forks) == -1)
		return ;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/last_meal");	
}*/
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
			printf("HOLABUENOSDIAS\n");
			while (i < philo->rules->nb_philo)
			{
				kill(philo->rules->philo[i].pid, SIGKILL);
				i++;
			}
			break;
		}
		i++;
	}
	if (sem_close(philo->rules->print) == -1 || sem_close(philo->rules->death) ==-1 || \
		sem_close(philo->rules->last_meal) == -1 || sem_close(philo->rules->forks) == -1)
		return ;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/last_meal");	
}
/*
int	check_death_flag(t_philo *philo)
{
	int	value;

	value = 0;
	if (sem_wait(philo->rules->death) == -1)
		return (-1);
	if (philo->rules->death_flag == 1)
	{
	printf("DEATHFLAG\n");
	value = 1;
	}
	if (sem_post(philo->rules->death) == -1)
		return (-1);
	return (value);
}
*/
void	philo_routine(t_philo *philo)
{
	if (pthread_create(&philo->end_check, NULL, check_end, philo))
		return ;
//	while (!check_death_flag(philo))
//	while (!philo->death_flag)
	while (1)
	{
		ft_eating(philo);
		ft_sleep(philo);
		print_action(philo, THINK);
		usleep(500);
	}
	if (pthread_join(philo->end_check, NULL))
		return ;
//	if (check_death_flag(philo))
//	if (philo->death_flag)
//		exit(1);

//	printf("JJJJJJJ");
//	exit(0);
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
//	if (pthread_create(&rules->end_check, NULL, &check_end, rules))
//		return ;
	while (i < rules->nb_philo)
	{
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == -1)
			return ;
		if (rules->philo[i].pid == 0)
			philo_routine(&rules->philo[i]);
	//	usleep(100);
		i++;
	}
//	if (pthread_join(rules->end_check, NULL))
//		return ;
	kill_and_close_sem(rules->philo);
}
