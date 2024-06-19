/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:54:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/19 17:55:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_table *table, t_philo *philo)
{
	int			target;

	target = philo->id;
	take_fork(table, table->forks[target], philo);
	print_ts(table, philo, TAKING_L_FORK);
}

void	take_right_fork(t_table *table, t_philo *philo)
{
	int			target;

	target = (philo->id + 1) % table->n_philos;
	take_fork(table, table->forks[target], philo);
	print_ts(table, philo, TAKING_R_FORK);
}

//	debug code for 'if (philo->status == DEAD)' to check deadlock conditions
	//{
		//printf("Philo %d died waiting for FORK %d\n", philo->id + 1, fork->id);
		//fflush(stdout);
	//}
void	take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	safe_mutex(&fork->mutex, LOCK);
	if (philo->status == DEAD)
		;
	else
	{
		if (fork->id == philo->id)
			philo->l_fork = fork;
		else if (fork->id == (philo->id + 1) % table->n_philos)
			philo->r_fork = fork;
		else
			printf("Philo %d got FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
	}
}
