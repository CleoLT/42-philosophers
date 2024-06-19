/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/19 22:22:50 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long long	time;
	
	time = get_time() - philo->rules->t_start;
	pthread_mutex_lock(&philo->rules->print);
	if (!philo->rules->death_flag)
		printf("%06lld\t%d\t%s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->rules->print);
}


int	check_alive(t_philo *philo)
{
	long long time_diff;

	time_diff = (get_time() - philo->t_last_meal);
	if (time_diff >= philo->rules->t_die)
	{	
		print_action(philo, DEATH);
	//	pthread_mutex_lock(&philo->rules->print);
		philo->rules->death_flag = 1;
	//	pthread_mutex_unlock(&philo->rules->print);
		return (1);
	}
	return (0);
}

void	ft_wait(t_philo *philo, int wait)
{
	long long time = get_time();

		while (!philo->rules->death_flag)
	{
		if (check_alive(philo))
			return ;
/*		
if (get_time() - philo->t_last_meal > philo->rules->t_die - 1)
		{
			print_action(philo, DEATH);
		//	philo->rules->death_flag = 1;
			return ;
		}*/
		if (get_time() - time >= wait)
		{
		break ;}
	}
}

void ft_sleep(t_philo *philo)
{
	ft_wait(philo, philo->rules->t_sleep);
	print_action(philo, SLEEP);
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
	
	init_forks_id(&first_fork, &sec_fork, philo->id, philo->rules->nb_philo);
	pthread_mutex_lock(&philo->rules->forks[sec_fork]);
	print_action(philo, FORKR);
	pthread_mutex_lock(&philo->rules->forks[first_fork]);
	print_action(philo, FORKL);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->rules->death);
	ft_wait(philo, philo->rules->t_eat);
//	printf("HOLI\n");
	pthread_mutex_unlock(&philo->rules->death);
//	printf("HOLIII\n");
	philo->t_last_meal = get_time();
	philo->nb_meal++;
//	ft_wait(philo, philo->rules->t_eat); //ICI CA MARCHE PAS
	pthread_mutex_unlock(&philo->rules->forks[sec_fork]);
	pthread_mutex_unlock(&philo->rules->forks[first_fork]);
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
