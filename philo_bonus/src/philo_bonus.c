/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:02 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 15:35:39 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_syntax(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				write(2, "philosophers accept only positive numbers\n", 42);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
	{
		write(2, "error: type almost 1 philosopher\n", 33);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	exec_philo(&rules);
	if (rules.philo)
		free(rules.philo);
	return (EXIT_SUCCESS);
}
