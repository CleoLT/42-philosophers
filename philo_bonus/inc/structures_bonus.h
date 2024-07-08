/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:22 by cle-tron          #+#    #+#             */
/*   Updated: 2024/07/08 13:53:10 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

# define FORK	" has taken a fork\t\xF0\x9F\x8D\xB4"
# define FORKR	" has taken R fork\t\xF0\x9F\x8D\xB4"
# define FORKL	" has taken L fork\t\xF0\x9F\x8D\xB4"
# define EAT	" is eating\t\t\xF0\x9F\x8D\xBD"
# define SLEEP	" is sleeping\t\t\xF0\x9F\x98\xB4"
# define THINK	" is thinking\t\t\xF0\x9F\xA4\x94"
# define DEATH	" died\t\t\t\xF0\x9F\x92\x80"

struct	s_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		end_check;
	pid_t			pid;
	long long		t_last_meal;
	int				nb_meal;
	int				is_eating;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				nb_eat;
	long long		t_start;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*last_meal;
}	t_rules;

#endif
