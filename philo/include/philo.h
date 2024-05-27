/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:56:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 18:40:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
} t_mutex_code;

typedef pthread_mutex_t t_mtx;

typedef struct	s_table t_table;
typedef struct	s_philo t_philo;
typedef struct	s_fork t_fork;

typedef struct s_table
{
	long	n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	n_limit_meals;
	long	start_time;
	int		end_sim;
	t_fork	*forks;
	t_philo	*philos;

}	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_phil
{
	int			id;
	pthread_t	thread_id;
	t_fork		*l_fork;
	t_fork		*r_fork;
	long		n_meals;
	int			full;
	long		last_meal_time;
	t_table		*table;
}	t_phil;

//	errors.c
int	check_input(t_table *table);

//	parse_input.c
int	parse_input(t_table *table, char *argv[]);

#endif
