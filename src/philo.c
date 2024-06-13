/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:02 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/13 18:00:17 by cle-tron         ###   ########.fr       */
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
				printf("%c\n", argv[i][j]);
				write(2, "philosophers accept only positive numbers\n", 42);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
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
	printf("%d, %d, %d, %d, %d\n", rules.nb_philo, rules.t_die, rules.t_eat, rules.t_sleep, rules.nb_eat);
	
	return (EXIT_SUCCESS);
}
