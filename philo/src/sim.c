/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/12 17:54:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_sim(t_table *table)
{
	(void) table;
}

int	start_sim(t_table *table)
{
	int	i;

	if (table->n_limit_meals == 0)
		return 0;
	if (table->n_philos == 1)
		return 0;
	else
	{
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		i = 0;
		/*printf("Sim starting at %ld, %ld\n", table->start_time.tv_sec, table->start_time.tv_usec);*/
		while (i < table->n_philos)
		{
			pthread_create(&table->philos[i]->thread_id, NULL, &routine_run, table->philos[i]);
			i++;
		}
		pthread_create(&table->monitor_id, NULL, &routine_monitor, table);
		while (table->end_sim == RUNNING)
			;
	}
	return 0;
}
