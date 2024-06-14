/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/14 17:52:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_full(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->n_philos)
	{
		status = get_phil_status(table->philos[i]);
		if (status == FULL)
			i++;
		else
			return ;
	}
	printf("Setting status to END_FULL\n");
	set_status(&table->mutex, &table->sim_status, END_FULL);
}

void	monitor_cycle(t_table *table, t_philo *philo, t_timestamp curr_time)
{
	int			status;
	/*t_timestamp last_meal;*/

	status = get_phil_status(philo);
	/*last_meal = get_ts(&philo->mutex, &philo->last_meal_time);*/
	if (status == DEAD)
		set_status(&table->mutex, &table->sim_status, END_DEAD);
	else if ((status == HUNGRY) && curr_time - philo->last_meal_time >= table->time_to_die)
	{
		set_status(&philo->mutex, &philo->status, DEAD);
		curr_time = ts_since_tv(table->start_time);
		printf("%d %d died\n", curr_time / MSEC, philo->id + 1);
		fflush(stdout);
	}
	else if (table->n_limit_meals == 0 || philo->n_meals < table->n_limit_meals)
		return ;
	else if (status != FULL)
		set_status(&philo->mutex, &philo->status, FULL);
}

void	*start_monitor(void *arg)
{
	t_table		*table;
	t_timestamp	curr_time;
	int			i;

	table = (t_table *)arg;
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
	curr_time = ts_since_tv(table->start_time);
	while (table->sim_status == RUNNING)
	{
		i = 0;
		while (RUNNING == table->sim_status && i < table->n_philos)
		{
			curr_time = ts_since_tv(table->start_time);
			monitor_cycle(table, table->philos[i], curr_time);
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
