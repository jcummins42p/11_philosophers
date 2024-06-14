/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/14 15:45:30 by jcummins         ###   ########.fr       */
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
	set_status(&table->mutex, &table->sim_status, END_FULL);
}

void	*routine_monitor(void *arg)
{
	t_table		*table;
	t_philo		*philo;
	t_timestamp	curr_time;
	int			i;
	int			status;

	table = (t_table *)arg;
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
	curr_time = ts_since_tv(table->start_time);
	while (table->sim_status == RUNNING)
	{
		i = 0;
		while (RUNNING == table->sim_status && i < table->n_philos)
		{
			philo = table->philos[i];
			status = get_phil_status(philo);
			curr_time = ts_since_tv(table->start_time);
			if (status == DEAD)
				set_status(&table->mutex, &table->sim_status, END_DEAD);
			else if ((status == HUNGRY) && curr_time - philo->last_meal_time >= table->time_to_die)
			{
				set_status(&philo->mutex, &philo->status, DEAD);
				curr_time = ts_since_tv(table->start_time);
				/*printf("%-10d Monitor: Philo %d is dead\n", curr_time / MSEC, philo->id + 1);*/
				printf("%d %d died\n", curr_time / MSEC, philo->id + 1);
				fflush(stdout);
			}
			else if (table->n_limit_meals == 0 || philo->n_meals < table->n_limit_meals)
				;
			else if (status != FULL)
			{
				set_status(&philo->mutex, &philo->status, FULL);
				curr_time = ts_since_tv(table->start_time);
				/*printf("%-10d Monitor: Philo %d is full\n", curr_time / MSEC, philo->id + 1);*/
				printf("%d %d is thinking\n", curr_time / MSEC, philo->id + 1);
				fflush(stdout);
			}
			i++;
		}
		check_full(table);
	}
	if (get_sim_status(table) == END_FULL)
		printf("Simulation ending: all philosophers are full\n");
	else if (get_sim_status(table) == END_DEAD)
		printf("Simulation ending: a philosopher has died\n");
	return (NULL);
}
