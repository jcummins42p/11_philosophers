/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/13 19:16:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_sim(t_table *table)
{
	(void) table;
}

int	start_sim(t_table *table)
{
	int			i;

	print_valid_input(table);
	if (table->n_philos > 0)
	{
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		table->starting_line = ts_since_tv(table->start_time) + MSEC * table->n_philos;
		i = -1;
		while (++i < table->n_philos)
		{
			if (pthread_create(&table->philos[i]->thread_id, NULL, &routine_run, table->philos[i]))
				printf("Error creating thread %d\n", table->philos[i]->id);
			usleep(1000);
		}
		pthread_create(&table->monitor_id, NULL, &routine_monitor, table);
		while (table->sim_status == RUNNING)
			usleep(1000);
		if (table->sim_status != RUNNING)
		{
			printf("Simulation registers end of simulation\n");
			i = 0;
			while (i < table->n_philos)
				pthread_join(table->philos[i++]->thread_id, NULL);
		}
		pthread_join(table->monitor_id, NULL);
	}
	return 0;
}
