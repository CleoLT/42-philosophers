/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_end_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 15:06:23 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int check_nb_meal(t_philo *philo)
{
//	usleep(100);
	if (philo->rules->nb_eat == -1)
		return (0);
	if (sem_wait(philo->rules->last_meal) == -1)
		return (-1);
	if (philo->nb_meal >= philo->rules->nb_eat)
	{
		printf("id : %d nb eat okkk HALOOO\n", philo->id+1);
if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
	exit(0);
	}
	if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
//	usleep(100);
	return (0);
}

int	check_death(t_philo *philo)
{
	long long	time_diff;

	if (sem_wait(philo->rules->last_meal) == -1)
			return (-1);
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff > philo->rules->t_die && philo->is_eating == 0)
	{
		print_action(philo, DEATH);
	//	if (sem_wait(philo->rules->death) == -1)
	//		return (-1);
//		philo->rules->death_flag = 1;
//		philo->death_flag = 1;
		sem_wait(philo->rules->print);
	printf("time diff : %lld,    t_last_meal: %lld\n", time_diff, philo->t_last_meal);
		if (/*sem_post(philo->rules->death) == -1 ||*/ sem_post(philo->rules->last_meal) == -1)
			return (-1);
		exit(1);
//		return (1);
		}
//	if (sem_post(philo->rules->last_meal) == -1)
//			return (-1);
	
//	if (philo->rules->death_flag)
//		return(1);
//	if (sem_wait(philo->rules->last_meal) == -1)
//		return (-1);
	if (philo->rules->nb_eat != -1 && philo->nb_meal >= philo->rules->nb_eat)
	{
		printf("id : %d nb eat okkk HALOOO\n", philo->id+1);
if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
	exit(0);
	}
	if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
	return (0);


}

void	*check_end(void *data)
{
	t_philo	*philo;
//	long long	time_diff;

	philo = (t_philo *)data;
	while (1)
	{
/*		usleep(200);
		if (sem_wait(philo->rules->last_meal) == -1)
			return (NULL);
		time_diff = (get_time() - philo->t_last_meal);
		if (time_diff > philo->rules->t_die && philo->is_eating == 0)
		{
			print_action(philo, DEATH);
			sem_wait(philo->rules->print);
			printf("time diff : %lld,    t_last_meal: %lld\n", time_diff, philo->t_last_meal);
			if (sem_post(philo->rules->last_meal) == -1)
				return (NULL);
			exit(1);
		}
		if (philo->rules->nb_eat > -1 && philo->nb_meal >= philo->rules->nb_eat)
		{
			printf("id : %d nb eat okkk HALOOO\n", philo->id+1);
			if (sem_post(philo->rules->last_meal) == -1)
				return (NULL);
			exit(0);
		}
		if (sem_post(philo->rules->last_meal) == -1)
			return (NULL);*/
		usleep(200);
		check_death(philo);
	}
}
