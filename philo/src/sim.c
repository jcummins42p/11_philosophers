/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/19 17:52:44 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_sim(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
		pthread_join(table->philos[i++]->thread_id, NULL);
	pthread_join(table->monitor_id, NULL);
	if (table->sim_status == END_DEAD)
		printf("Simulation ends: a philosopher has died\n");
	else if (table->sim_status == END_FULL)
		printf("Simulation ends: all philosophers are full\n");
	fflush(stdout);
	return (0);
}

int	spawn_philos(pthread_t *thread_id, t_philo *philo)
{
	if (pthread_create(thread_id, NULL, &start_routine, philo))
		return (1);
	else
		return (0);
}

void	set_starting_line(t_table *table)
{
	t_timestamp	output;
	int			mp;

	mp = 100;
	output = ts_since_tv(table->start_time) + (MSEC * mp * table->n_philos);
	table->starting_line = output;
}

int	start_sim(t_table *table)
{
	int			i;

	if (table->n_philos > 0)
	{
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		set_starting_line(table);
		i = -1;
		while (++i < table->n_philos)
			if (spawn_philos(&table->philos[i]->thread_id, table->philos[i]))
				error_exit(THREAD_FAIL);
		pthread_create(&table->monitor_id, NULL, &start_monitor, table);
		while (table->sim_status == RUNNING)
			usleep(10000);
	}
	return (0);
}
