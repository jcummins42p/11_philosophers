/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/19 21:46:33 by jcummins         ###   ########.fr       */
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
	set_status(&table->mutex, &table->sim_status, END_FULL);
}

void	monitor_cycle(t_table *table, t_philo *philo, t_timestamp curr_time)
{
	int			status;
	t_timestamp	lmt;

	lmt = get_ts(&philo->mutex, &philo->last_meal_time);
	if (curr_time - lmt > table->time_to_die + 500)
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
	pusleep(table->starting_line - curr_time);
	/*pthread_barrier_wait(&table->start_barrier);*/
	curr_time = ts_since_tv(table->start_time);
	status = get_int(&table->mutex, &table->sim_status);
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
		check_full(table);
	}
	return (NULL);
}
