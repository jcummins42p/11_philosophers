/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 19:22:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_cycle(t_table *table, t_philo *philo, t_timestamp curr_time)
{
	int			status;
	t_timestamp	lmt;

	lmt = get_ts(&philo->mutex, &philo->last_meal_time);
	if (curr_time - lmt > table->time_to_die + DEATH_MOD)
	{
		status = get_phil_status(philo);
		if (status == EATING || status == FULL)
			return ;
		else
		{
			set_status(&philo->mutex, &philo->status, DEAD);
			set_status(&table->mutex, &table->sim_status, END_DEAD);
			usleep(MSEC);
			print_ts(table, philo, DEAD);
		}
	}
	else if (table->n_limit_meals == 0 || philo->n_meals < table->n_limit_meals)
		return ;
	else
		set_status(&philo->mutex, &philo->status, FULL);
}

void	*start_monitor(void *arg)
{
	t_table		*table;
	t_timestamp	curr_time;
	int			i;
	int			status;

	table = (t_table *)arg;
	curr_time = ts_since_tv(table->start_time);
	status = get_int(&table->mutex, &table->sim_status);
	safe_mutex(&table->mutex, LOCK);
	safe_mutex(&table->mutex, UNLOCK);
	usleep(table->time_to_die);
	while (status == RUNNING)
	{
		i = 0;
		while (i < table->n_philos && status == RUNNING)
		{
			curr_time = ts_since_tv(table->start_time);
			monitor_cycle(table, table->philos[i], curr_time);
			status = get_int(&table->mutex, &table->sim_status);
			i++;
		}
		if (get_int(&table->mutex, &table->n_hungry_philos) == 0)
			set_status(&table->mutex, &table->sim_status, END_FULL);
	}
	return (NULL);
}
