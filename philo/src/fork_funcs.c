/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:54:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/14 16:55:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*take_left_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;
	t_timestamp	lfork_start;

	lfork_start = ts_since_tv(table->start_time);
	target = philo->id;
	out = take_fork(table, table->forks[target], philo);
	lfork_start = ts_since_tv(table->start_time);
	printf("%d %d has taken a fork\n", lfork_start / MSEC, philo->id + 1);
	fflush(stdout);
	return (out);
}

void	*take_right_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;
	t_timestamp	rfork_start;

	rfork_start = ts_since_tv(table->start_time);
	target = (philo->id + 1) % table->n_philos;
	out = take_fork(table, table->forks[target], philo);
	rfork_start = ts_since_tv(table->start_time);
	printf("%d %d has taken a fork\n", rfork_start / MSEC, philo->id + 1);
	fflush(stdout);
	return (out);
}

void	*take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	safe_mutex(&fork->mutex, LOCK);
	if (philo->status == DEAD)
		printf("Philo %d died waiting for FORK %d\n", philo->id + 1, fork->id);
	else
	{
		if (fork->id == philo->id)
			philo->l_fork = fork;
		else if (fork->id == (philo->id + 1) % table->n_philos)
			philo->r_fork = fork;
		else
			printf("Philo %d got FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
	}
	return (NULL);
}
