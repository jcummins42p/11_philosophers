/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:54:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 17:24:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_both_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	philo->r_fork = NULL;
	philo->l_fork = NULL;
}

void	take_fork_one(t_table *table, t_philo *philo)
{
	int			target;

	target = philo->id;
	take_fork(table, table->forks[target], philo);
}

void	take_fork_two(t_table *table, t_philo *philo)
{
	int			target;

	if (table->n_philos == 1)
	{
		while (get_sim_status(table) == RUNNING)
			psleep(MSEC, table);
		return ;
	}
	target = (philo->id + 1) % table->n_philos;
	take_fork(table, table->forks[target], philo);
}

void	take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex);
	if (get_philo_status(philo) != DEAD && get_sim_status(table) == RUNNING)
	{
		if (philo->id + 1 == table->n_philos)
		{
			if (fork->id == philo->id)
				philo->r_fork = fork;
			else if (fork->id == 0)
				philo->l_fork = fork;
			else
				printf("Philo %d FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
		}
		else
		{
			if (fork->id == philo->id)
				philo->l_fork = fork;
			else if (fork->id == philo->id + 1)
				philo->r_fork = fork;
			else
				printf("Philo %d FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
		}
	}
	else
		pthread_mutex_unlock(&fork->mutex);
}
