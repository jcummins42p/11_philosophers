/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/11 20:34:57 by jcummins         ###   ########.fr       */
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

	if (table->n_limit_meals == 0)
		return 0;
	else if (table->n_philos == 1)
		return 0;
	else
	{
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		while(1)
		{
			i = 0;
			printf("Sim starting at %ld, %ld\n", table->start_time.tv_sec, table->start_time.tv_usec);
			while (i < table->n_philos)
			{
				/*table->philos[i]->thread_id = (pthread_t)take_left_fork(table, table->philos[i]);*/
				/*table->philos[i]->thread_id = (pthread_t)take_right_fork(table, table->philos[i]);*/
				/*gettimeofday(t_simstart, NULL);*/
				table->philos[i]->thread_id = (pthread_t)routine_run(table, table->philos[i]);
				printf(KDEF);
				i++;
			}
			usleep(200000000);
		}
	}
	return 0;
}
