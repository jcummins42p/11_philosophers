/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 15:29:08 by jcummins         ###   ########.fr       */
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
		safe_mutex(&table->mutex, LOCK);
		i = -1;
		while (++i < table->n_philos)
			if (spawn_philos(&table->philos[i]->thread_id, table->philos[i]))
			{
				printf("Thread not made\n");
				error_exit(THREAD_FAIL);
			}
		if (gettimeofday(&table->start_time, NULL))
			error_exit(TIME_FAIL);
		pthread_create(&table->monitor_id, NULL, &start_monitor, table);
		safe_mutex(&table->mutex, UNLOCK);
	}
	return (0);
}
