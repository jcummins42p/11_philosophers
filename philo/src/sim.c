/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/31 16:41:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_sim(t_table *table)
{
	(void) table;
}

int	start_sim(t_table *table)
{
	int				i;
	struct timeval	*t_simstart;

	t_simstart = malloc(sizeof(struct timeval));
	if (table->n_limit_meals == 0)
		return 0;
	else if (table->n_philos == 1)
		return 0;
	else
	{
		while(1)
		{
			i = 0;
			while (i < table->n_philos)
			{
				table->philos[i]->thread_id = (pthread_t)wait(&i);
				table->philos[i]->thread_id = (pthread_t)take_fork(table->forks[i], table->philos[i]);
				gettimeofday(t_simstart, NULL);
				printf("Sim starting at %ld, %ld\n", t_simstart->tv_sec, t_simstart->tv_usec);
				if (table->philos[i]->state == THINKING)
					printf("Philosopher %d is thinking\n", table->philos[i]->id);
				else if (table->philos[i]->state == HUNGRY)
					printf(KYEL "Philosopher %d is hungry\n", table->philos[i]->id);
				else if (table->philos[i]->state == EATING)
					printf(KGRN "Philosopher %d is eating\n", table->philos[i]->id);
				else if (table->philos[i]->state == DEAD)
					printf(KRED "Philosopher %d is dead\n", table->philos[i]->id);
				printf(KDEF);
				i++;
			}
			usleep(2000000);
		}
	}
	return 0;
}
