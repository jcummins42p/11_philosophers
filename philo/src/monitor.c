/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/13 14:44:36 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (table->philos[i]->status == FULL)
			i++;
		else
			return ;
	}
	printf("Setting status to END_FULL\n");
	table->sim_status = END_FULL;
}



void	*routine_monitor(void *arg)
{
	t_table		*table;
	t_timestamp	curr_time;
	int			i;

	table = (t_table *)arg;
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
	curr_time = ts_since_tv(table->start_time);
	printf("Starting monitor at %d\n", curr_time);
	while (table->sim_status == RUNNING)
	{
		i = 0;
		while (RUNNING == table->sim_status && i < table->n_philos)
		{
			curr_time = ts_since_tv(table->start_time);
			if (table->philos[i]->status == DEAD)
				table->sim_status = END_DEAD;
			else if (table->philos[i]->status == HUNGRY && curr_time - table->philos[i]->last_meal_time >= table->time_to_die)
			{
				curr_time = ts_since_tv(table->start_time);
				printf("%-10d Monitor: Philo %d is dead\n", curr_time, table->philos[i]->id + 1);
				table->philos[i]->status = DEAD;
			}
			else if (table->n_limit_meals == 0 || table->philos[i]->n_meals < table->n_limit_meals)
				;
			else if (table->philos[i]->status != FULL)
			{
				curr_time = ts_since_tv(table->start_time);
				printf("%-10d Monitor: Philo %d is full\n", curr_time, table->philos[i]->id + 1);
				table->philos[i]->status = FULL;
			}
			i++;
		}
		check_full(table);
	}
	if (table->sim_status == END_FULL)
		printf("Simulation ending: all philosophers are full\n");
	else if (table->sim_status == END_DEAD)
		printf("Simulation ending: a philosopher has died\n");
	return (NULL);
}
