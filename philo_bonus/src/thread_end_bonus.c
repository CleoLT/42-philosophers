/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_end_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:18:23 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/05 14:43:45 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/*
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
		if (sem_wait(rules->last_meal) == -1)
			return (-1);
		if (rules->philo[i].nb_meal >= rules->nb_eat)
			count++;
		if (sem_post(rules->last_meal) == -1)
			return (-1);	
		i++;
	}
	if (count >= rules->nb_philo)
	{
	//	pthread_mutex_lock(&rules->death);
//	printf("HIIIIIII\n");
		if (sem_wait(rules->death) == -1)
			return (-1);
		rules->death_flag = 1;
		if (sem_post(rules->death) == -1)
			return (-1);	
	//	pthread_mutex_unlock(&rules->death);
		return (1);
	}
	usleep(100);
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	long long	time_diff;
//	static int i = 0;

		//	pthread_mutex_lock(&philo->rules->last_meal);
	if (sem_wait(philo->rules->last_meal) == -1)
			return (-1);
	time_diff = (get_time() - philo->t_last_meal);
//	if ( i++ % 1000 == 0)
//		printf("%lld philo->t_last_meal funct\n",philo->t_last_meal);
	if (time_diff > philo->rules->t_die && philo->is_eating == 0)
	{
		print_action(philo, DEATH);
		if (sem_wait(philo->rules->death) == -1)
			return (-1);
//		pthread_mutex_lock(&philo->rules->death);
		philo->rules->death_flag = 1;
printf("time diff : %lld,    t_last_meal: %lld\n", time_diff, philo->t_last_meal);
		if (sem_post(philo->rules->death) == -1 || sem_post(philo->rules->last_meal) == -1)
			return (-1);
//		pthread_mutex_unlock(&philo->rules->death);
//		pthread_mutex_unlock(&philo->rules->last_meal);
				return (1);
		}
//	pthread_mutex_unlock(&philo->rules->last_meal);
	if (sem_post(philo->rules->last_meal) == -1)
			return (-1);
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
	//	usleep(1000);
			i++;
	}
	return (0);
}
*/

int	check_death(t_philo *philo)
{
	long long	time_diff;

	if (sem_wait(philo->rules->last_meal) == -1)
			return (-1);
	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff > philo->rules->t_die && philo->is_eating == 0)
	{
		print_action(philo, DEATH);
		if (sem_wait(philo->rules->death) == -1)
			return (-1);
		philo->rules->death_flag = 1;
		philo->death_flag = 1;
		sem_wait(philo->rules->print);
	printf("time diff : %lld,    t_last_meal: %lld\n", time_diff, philo->t_last_meal);
		if (sem_post(philo->rules->death) == -1 || sem_post(philo->rules->last_meal) == -1)
			return (-1);
		exit(1);
		return (1);
		}
	if (sem_post(philo->rules->last_meal) == -1)
			return (-1);
//	if (philo->rules->death_flag)
//		return(1);
//	usleep(200);
	return (0);


}

int check_nb_meal(t_philo *philo)
{
//	usleep(100);
	if (philo->rules->nb_eat == -1)
		return (0);
	if (sem_wait(philo->rules->last_meal) == -1)
		return (-1);
	if (philo->nb_meal >= philo->rules->nb_eat)
	{
		printf("id : %d nb eat okkk HALOOO", philo->id+1);
if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
	exit (0);
	}
	if (sem_post(philo->rules->last_meal) == -1)
		return (-1);
//	usleep(100);
	return (0);
}

void	*check_end(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
	/*	if (check_death(philo))// ||  check_nb_meal(rules))
		{
	printf("HIIIII");
			exit(1);
			return (NULL);
		}
		if (check_nb_meal(philo))
			exit(0);*/
		check_death(philo);
		check_nb_meal(philo);
		usleep(200);
	}
}
