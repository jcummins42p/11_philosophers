/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/12 18:50:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_monitor(void *arg)
{
	t_table		*table;
	t_timestamp	curr_time;
	int			i;

	table = (t_table *)arg;
	while (table->sim_status == RUNNING)
	{
		i = 0;
		while (i < table->n_philos)
		{
			curr_time = get_time_since(table->start_time);
			if (table->philos[i]->status == DEAD)
			{
				table->sim_status = END_DEAD;
			}
			else if (table->philos[i]->status == HUNGRY && curr_time - table->philos[i]->last_meal_time >= table->time_to_die)
			{
				printf("Current time: %d\nPhilo %d last meal time: %d\nTime to die: %ld\n", curr_time, table->philos[i]->id, table->philos[i]->last_meal_time, table->time_to_die);
				printf("\tMonitor: Philo %d is dead\n", table->philos[i]->id);
				table->philos[i]->status = DEAD;
			}
			else if (table->n_limit_meals == 0 || table->philos[i]->n_meals < table->n_limit_meals)
				;
			else if (table->philos[i]->n_meals >= table->n_limit_meals && table->philos[i]->status != FULL)
			{
				printf("\tMonitor: Philo %d is full\n", table->philos[i]->id);
				table->philos[i]->status = FULL;
			}
			i++;
		}
	}
	if (table->sim_status == END_FULL)
		printf("Simulation ending: all philosophers are full\n");
	else if (table->sim_status == END_DEAD)
		printf("Simulation ending: a philosopher has died\n");
	return (NULL);
}
