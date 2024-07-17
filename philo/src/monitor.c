/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:46 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/17 14:06:07 by jcummins         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mutex);
	curr_time = ts_since_tv(philo->start_time);
	pthread_mutex_unlock(&philo->mutex);
	time_since_food = curr_time - get_ts(&philo->mutex, &philo->last_meal_time);
	if (time_since_food > table->time_to_die + DEATH_MOD)
		dead = true;
	return (dead);
}

bool	phil_now_full(t_table *table, t_philo *philo)
{
	int		n_meals;

	n_meals = get_int(&philo->mutex, &philo->n_meals);
	if (table->n_limit_meals != 0 && n_meals >= table->n_limit_meals)
	{
		set_bool(&philo->mutex, &philo->full, true);
		return (true);
	}
	else
		return (false);
}

void	monitor_checks(t_table *table, t_philo *philo)
{
	bool	full;

	if (died_of_hunger(table, philo))
	{
		set_philo_status(philo, DEAD);
		set_sim_status(table, END_DEAD);
		usleep(MSEC);
		print_ts(table, philo, DEAD);
	}
	else if (table->n_limit_meals != 0)
	{
		full = get_bool(&philo->mutex, &philo->full);
		if (!full && phil_now_full(table, philo))
			set_decrement(&table->mutex, &table->n_hungry);
	}
}

void	monitor_cycle(t_table *table)
{
	int	i;

	while (get_sim_status(table) == RUNNING)
	{
		i = 0;
		while (i < table->n_philos && get_sim_status(table) == RUNNING)
			monitor_checks(table, table->philos[i++]);
		if (get_sim_status(table) == RUNNING && \
			get_int(&table->mutex, &table->n_hungry) == 0)
			set_sim_status(table, END_FULL);
	}
}

void	*start_monitor(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	while (get_sim_status(table) == WAITING)
		;
	psleep(table->time_to_die, table);
	if (table->n_philos == 1)
	{
		set_sim_status(table, END_DEAD);
		print_ts(table, table->philos[0], DEAD);
	}
	else
		monitor_cycle(table);
	return (NULL);
}
