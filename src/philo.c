/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:02 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/14 17:22:45 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_syntax(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, "philosophers accept only positive numbers\n", 42);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


t_philo	*init_philosophers(t_rules *rules)
{
	int		i;
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo ) * rules->nb_philo);
	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i;
		philo[i].t_last_meal = 0;
		philo[i].nb_meal = 0;
		philo[i].rules = rules;
		i++;
	}
	return (philo);
}

void	init_rules(char **argv, t_rules *rules)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->nb_eat = ft_atoi(argv[5]);
	else
		rules->nb_eat = -1;
	rules->t_start = get_time();
	rules->philo = init_philosophers(rules);
}

void	print_philos(t_philo *philo, int nb_philo)
{
	int i = 0;
	while (i < nb_philo)
	{
		printf("philo id : %d\t", philo[i].id);
		i++;
	}
}

void	free_all(t_rules rules)
{
	free(rules.philo);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
	{
		write(2, "philosophers needs, 5 o 6 arguments\n", 36);
		return (EXIT_FAILURE);
	}
	if (error_syntax(argv))
		return (EXIT_FAILURE);
	init_rules(argv, &rules);
//	printf("%d, %d, %d, %d, %d, %lld\n", rules.nb_philo, rules.t_die, rules.t_eat, rules.t_sleep, rules.nb_eat, rules.t_start);
//	printf(DIED);
//	printf(FORK);
//	printf(EAT);
//	printf(SLEEP);
//	printf(THINK);

//	print_philos(rules.philo, rules.nb_philo);
	exec_philo(&rules);
	free_all(rules);
	return (EXIT_SUCCESS);
}
