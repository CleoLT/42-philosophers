/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-tron <cle-tron@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:22 by cle-tron          #+#    #+#             */
/*   Updated: 2024/06/17 13:48:21 by cle-tron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define FORK	" has taken a fork\t\xF0\x9F\x8D\xB4"
# define FORKR	" has taken R fork\t\xF0\x9F\x8D\xB4"
# define FORKL	" has taken L fork\t\xF0\x9F\x8D\xB4"
# define EAT	" is eating\t\t\xF0\x9F\x8D\xBD"
# define SLEEP	" is sleeping\t\t\xF0\x9F\x98\xB4"
# define THINK	" is thinking\t\t\xF0\x9F\xA4\x94"
# define DEATH	" died\t\t\t\xF0\x9F\x92\x80"

struct s_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		t_last_meal;
	int				nb_meal;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	long long		t_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int				death_flag;
}	t_rules;



#endif
