/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:54:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/10 18:39:06 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_one(t_table *table, t_philo *philo)
{
	int			target;

	target = philo->id;
	take_fork(table, table->forks[target], philo);
	print_ts(table, philo, TAKING_L_FORK);
	/*printf("(fork %d)\n", target + 1);*/
	/*fflush(stdout);*/
}

void	take_fork_two(t_table *table, t_philo *philo)
{
	int			target;

	if (table->n_philos == 1)
		return ;
	target = (philo->id + 1) % table->n_philos;
	take_fork(table, table->forks[target], philo);
	print_ts(table, philo, TAKING_R_FORK);
	/*printf("(fork %d)\n", target + 1);*/
	/*fflush(stdout);*/
}

//	debug code for 'if (philo->status == DEAD)' to check deadlock conditions
	//{
		//printf("Philo %d died waiting on FORK %d\n", philo->id + 1, fork->id);
		//fflush(stdout);
	//}
void	take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	/*safe_mutex(&fork->mutex, LOCK);*/
	pthread_mutex_lock(&fork->mutex);
	if (get_int(&philo->mutex, &philo->status) != DEAD && get_int(&table->mutex, &table->sim_status) == RUNNING)
	{
		if (philo->id + 1 == table->n_philos)
		{
			if (fork->id == philo->id)
				philo->r_fork = fork;
			else if (fork->id == 0)
				philo->l_fork = fork;
			else
				printf("Philo %d got FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
		}
		else
		{
			if (fork->id == philo->id)
				philo->l_fork = fork;
			else if (fork->id == philo->id + 1)
				philo->r_fork = fork;
			else
				printf("Philo %d got FORBIDDEN FORK %d\n", philo->id + 1, fork->id);
		}
	}
}
