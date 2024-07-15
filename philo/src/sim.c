/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 17:13:07 by jcummins         ###   ########.fr       */
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
	if (get_sim_status(table) == END_DEAD)
		printf("Simulation ends: a philosopher has died\n");
	else if (get_sim_status(table) == END_FULL)
		printf("Simulation ends: all philosophers are full\n");
	fflush(stdout);
	return (0);
}

int	spawn_philos(pthread_t *thread_id, t_philo *philo)
{
	if (pthread_create(thread_id, NULL, &start_routine, philo))
		{
			/*printf("Error creating philosopher thread %d\n", philo->id);*/
			return (1);
		}
	else
		{
			/*printf("Success creating philosopher thread %d\n", philo->id);*/
			return (0);
		}
}

int	start_sim(t_table *table)
{
	int			i;

	if (table->n_philos > 0)
	{
		set_status(&table->mutex, &table->sim_status, WAITING);
		i = 0;
		while (i < table->n_philos)
		{
			if (spawn_philos(&table->philos[i]->thread_id, table->philos[i]))
			{
				printf("Thread not made\n");
				error_exit(THREAD_FAIL);
			}
			i++;
		}
		pthread_create(&table->monitor_id, NULL, &start_monitor, table);
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		set_status(&table->mutex, &table->sim_status, RUNNING);
	}
	return (0);
}
