/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/29 20:28:11 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_philo *philo)
{
	int	value;

	value = 0;
	pthread_mutex_lock(&philo->rules->death);
	if (philo->rules->death_flag == 1)
		value = 1;
	pthread_mutex_unlock(&philo->rules->death);
//	if (philo->rules->nb_philo % 2 != 0)
		usleep(5);
	return (value);
}

void	print_action(t_philo *philo, char *action)
{
	long long	time;
	
	time = get_time() - philo->rules->t_start;
	pthread_mutex_lock(&philo->rules->print);
	if (!check_death_flag(philo))
		printf("%06lld\t%d\t%s\n", time, philo->id + 1, action);
	pthread_mutex_unlock(&philo->rules->print);
}
/*
int	check_alive(t_philo *philo)
{
	long long time_diff;

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
}*/

void	ft_wait(t_philo *philo, int wait)
{
	long long time = get_time();

	while (!check_death_flag(philo))
		if (get_time() - time >= wait)
			break ;
}

void ft_sleep(t_philo *philo)
{
	ft_wait(philo, philo->rules->t_sleep);
	print_action(philo, SLEEP);
}

void	ft_eating(t_philo *philo)
{
	int	first_fork;
	int	sec_fork;

	init_forks_id(&first_fork, &sec_fork, philo->id, philo->rules->nb_philo);
	pthread_mutex_lock(&philo->rules->forks[sec_fork]);
	print_action(philo, FORKR);
	pthread_mutex_lock(&philo->rules->forks[first_fork]);
	print_action(philo, FORKL);
	print_action(philo, EAT);
//	pthread_mutex_lock(&philo->rules->count_meal);	
//	philo->nb_meal++;
//	pthread_mutex_unlock(&philo->rules->count_meal);

	pthread_mutex_lock(&philo->rules->last_meal);	
	philo->t_last_meal = get_time();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->rules->last_meal);
	ft_wait(philo, philo->rules->t_eat);
//	pthread_mutex_lock(&philo->rules->count_meal);	
//	philo->nb_meal++;
//	pthread_mutex_unlock(&philo->rules->count_meal);
	pthread_mutex_unlock(&philo->rules->forks[sec_fork]);
	pthread_mutex_unlock(&philo->rules->forks[first_fork]);
}


void	*philo_routine(void *data)
{
//	pthread_t	t;
	t_philo		*philo;

//	t = pthread_self();
	philo = (t_philo *)data;

	while (!check_death_flag(philo))
	{
	//	printf("thread nb: %ld, philo id: %d\n", t, philo->id);
	//	if (check_alive(philo))
	//		return (NULL);
		ft_eating(philo);
		ft_sleep(philo);
		print_action(philo, THINK);
	//	if (check_alive(philo))
	//		return (NULL);

	}
	return (NULL);
}


void	exec_philo(t_rules *rules)
{
	int i;
	int	*idx;
	
	i = 0;
	idx = NULL;
	if (rules->nb_philo == 1)
	{
		print_action(rules->philo, FORK);
		usleep(rules->t_die * 1000);
		print_action(rules->philo, DEATH);
		return ;
	}
	init_index(&idx, rules->nb_philo);
//	printf("%d nb_eat\n", rules->nb_eat);
	pthread_create(&rules->finish, NULL, check_end, rules);
	while (i < rules->nb_philo)
	{
		pthread_create(&rules->philo[idx[i]].thread, NULL, philo_routine, &rules->philo[idx[i]]);
		i++;
	}
	pthread_join(rules->finish, NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[idx[i]].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[idx[i]]);
		i++;
	}
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->death);
	pthread_mutex_destroy(&rules->last_meal);
	pthread_mutex_destroy(&rules->count_meal);
	free(idx);
}
