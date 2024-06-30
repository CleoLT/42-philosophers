/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:02 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/30 16:43:25 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	free_all(t_rules rules)
{
	free(rules.philo);
	free(rules.forks);
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
	free_all(rules);
	return (EXIT_SUCCESS);
}
