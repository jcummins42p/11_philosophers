/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 17:48:14 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	died_of_hunger(t_table *table, t_philo *philo)
{
	t_timestamp	time_since_food;
	t_timestamp	curr_time;
	bool		dead;

	time_since_food = 0;
	dead = false;
	curr_time = ts_since_tv(table->start_time);
	time_since_food = curr_time - get_ts(&philo->mutex, &philo->last_meal_time);
	if (time_since_food > table->time_to_die + DEATH_MOD)
		dead = true;
	return (dead);
}

void	monitor_cycle(t_table *table, t_philo *philo)
{
	int		n_meals;
	bool	dead;

	n_meals = get_int(&philo->mutex, &philo->n_meals);
	dead = false;
	dead = died_of_hunger(table, philo);
	if (dead)
	{
		set_status(&philo->mutex, &philo->status, DEAD);
		set_status(&table->mutex, &table->sim_status, END_DEAD);
		usleep(MSEC);
		print_ts(table, philo, DEAD);
	}
	else if (table->n_limit_meals != 0 && n_meals == table->n_limit_meals)
		set_decrement(&table->mutex, &table->n_hungry_philos);
}

void	*start_monitor(void *arg)
{
	t_table		*table;
	int			status;
	int			i;

	table = (t_table *)arg;
	status = WAITING;
	i = 0;
	/*safe_mutex(&table->mutex, LOCK);*/
	/*safe_mutex(&table->mutex, UNLOCK);*/
	usleep(table->time_to_die);
	while (status == WAITING)
		status = get_sim_status(table);
	while (status == RUNNING)
	{
		i = 0;
		while (i < table->n_philos && status == RUNNING)
		{
			monitor_cycle(table, table->philos[i]);
			status = get_int(&table->mutex, &table->sim_status);
			i++;
		}
		if (get_int(&table->mutex, &table->n_hungry_philos) == 0)
			set_status(&table->mutex, &table->sim_status, END_FULL);
	}
	return (NULL);
}
