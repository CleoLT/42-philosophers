/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:35:59 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/14 17:49:43 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *data)
{
	pthread_t	t;
	t_philo		*philo;

	t = pthread_self();
	philo = (t_philo *)data;
	printf("thread nb: %ld, philo id: %d, t_sleep: %d\n", t, philo->id);
	return (NULL);
}

void	exec_philo(t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_create(&rules->philo[i].thread, NULL, philo_routine, &rules->philo[i]);		




		i++;
	}







}
