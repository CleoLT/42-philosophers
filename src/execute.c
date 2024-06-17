/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/17 14:02:34 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long long	time;
	
//	if (philo->rules->death_flag)
//		return ;
	pthread_mutex_lock(&philo->rules->print);
	time = get_time() - philo->rules->t_start;
	printf("%06lld\t%d\t%s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->rules->print);
}

void ft_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->rules->t_sleep * 1000);
}

void	init_forks_id(int *first, int *sec, int id, int size)
{
	if (id == 0)
		*first = size - 1 ;
	else if (id % 2 == 0)
		*first = id - 1;
	else if (id % 2 != 0)
		*first = id;
	if (id % 2 != 0)
		*sec = id - 1;
	else 
		*sec = id;
}

void	ft_eating(t_philo *philo)
{
	int	first_fork;
	int	sec_fork;

/*	if (philo->id == 0)
		first_fork = philo->rules->nb_philo - 1 ;
	else if (philo->id % 2 == 0)
		first_fork = philo->id - 1;
	else if (philo->id % 2 != 0)
		first_fork = philo->id;
	if (philo->id%2 != 0)
		sec_fork = philo->id - 1;
	else 
		sec_fork = philo->id;*/
	init_forks_id(&first_fork, &sec_fork, philo->id, philo->rules->nb_philo);
	pthread_mutex_lock(&philo->rules->forks[sec_fork]);
	print_action(philo, FORKR);
	pthread_mutex_lock(&philo->rules->forks[first_fork]);
	print_action(philo, FORKL);
	print_action(philo, EAT);
	philo->t_last_meal = get_time();
	philo->nb_meal++;
//	while (1)
//		if ((get_time() - philo->t_last_meal) >= philo->rules->t_eat)
//			break ;
	
	usleep(philo->rules->t_eat * 1000);
//	ft_sleep(philo);
	pthread_mutex_unlock(&philo->rules->forks[sec_fork]);
	pthread_mutex_unlock(&philo->rules->forks[first_fork]);


}

int	check_alive(t_philo *philo)
{
	int time_diff = (get_time() - philo->t_last_meal);
	printf("time difference: %d, : %d\n", time_diff, philo->rules->t_die);
	if (time_diff >= philo->rules->t_die)
	{
		pthread_mutex_lock(&philo->rules->death);
		philo->rules->death_flag = 1;
		print_action(philo, DEATH);
		pthread_mutex_unlock(&philo->rules->death);
			return (1);
	}
	return (0);
}

void	*philo_routine(void *data)
{
//	pthread_t	t;
	t_philo		*philo;

//	t = pthread_self();
	philo = (t_philo *)data;
	while (1)//!philo->rules->death_flag)
	{
	//	printf("thread nb: %ld, philo id: %d\n", t, philo->id);
		if (check_alive(philo))
			return (NULL);
		ft_eating(philo);
		if (check_alive(philo))
			return (NULL);
		ft_sleep(philo);
		if (check_alive(philo))
			return (NULL);
		print_action(philo, THINK);
	//	if (get_time() > (philo->rules->t_start + 1000))
	//		break ;
			//philo->rules->death_flag = 1;
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
	while (i < rules->nb_philo)
	{
		pthread_create(&rules->philo[idx[i]].thread, NULL, philo_routine, &rules->philo[idx[i]]);
		i++;
	}
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
	free(idx);
}
