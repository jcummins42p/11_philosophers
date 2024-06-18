/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/18 18:14:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_sleep(t_table *table, t_philo *philo)
{
	t_timestamp	sleep_start;

	if (get_int(&philo->mutex, &philo->status) != DEAD)
	{
		sleep_start = ts_since_tv(table->start_time);
		set_status(&philo->mutex, &philo->status, SLEEPING);
		printf("%d %d is sleeping\n", sleep_start / MSEC, philo->id + 1);
		fflush(stdout);
		pusleep(table->time_to_sleep);
		if (get_int(&philo->mutex, &philo->status) != DEAD)
		{
			if (get_int(&philo->mutex, &philo->n_meals) < table->n_limit_meals)
				set_status(&philo->mutex, &philo->status, HUNGRY);
		}
	}
}

void	routine_eat(t_table *table, t_philo *philo)
{
	t_timestamp	eat_start;

	if (philo->status == HUNGRY)
	{
		set_status(&philo->mutex, &philo->status, EATING);
		eat_start = ts_since_tv(table->start_time);
		set_ts(&philo->mutex, &philo->last_meal_time, eat_start + table->time_to_eat);
		printf("%d %d is eating\n", eat_start / MSEC, philo->id + 1);
		fflush(stdout);
		pusleep(table->time_to_eat);
		philo->n_meals += 1;
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
		philo->l_fork = NULL;
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
		philo->r_fork = NULL;
		if (philo->n_meals == table->n_limit_meals)
			set_status(&philo->mutex, &philo->status, FULL);
	}
}

void	routine_cycle(t_table *table, t_philo *philo)
{
	t_timestamp	curr_time;

	curr_time = ts_since_tv(table->start_time);
	printf("%d %d is thinking\n", curr_time / MSEC, philo->id + 1);
	fflush(stdout);
	if (philo->status == HUNGRY && table->sim_status == RUNNING)
	{
		pusleep(200);
		take_left_fork(table, philo);
	}
	if (philo->status == HUNGRY && table->sim_status == RUNNING)
		take_right_fork(table, philo);
	if (philo->l_fork && philo->r_fork && table->sim_status == RUNNING)
		routine_eat(table, philo);
	if (philo->status != DEAD && table->sim_status == RUNNING)
		routine_sleep(table, philo);
}

//  ==	Debug lines to demonstrate co-ordination of philosophers
//		printf("Starting philo %d at %d\n", philo->id + 1, curr_time);
//		fflush(stdout);
void	*start_routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	t_timestamp	curr_time;

	philo = (t_philo *)arg;
	table = philo->table;
	set_ts(&philo->mutex, &philo->last_meal_time, table->starting_line);
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
	curr_time = ts_since_tv(table->start_time);
	if (philo->id % 2)
		routine_sleep(table, philo);
	while (philo->status == HUNGRY)
	{
		routine_cycle(table, philo);
	}
	if (table->sim_status == RUNNING)
	{
		curr_time = ts_since_tv(table->start_time);
		printf("%d %d is thinking at the end\n", curr_time / MSEC, philo->id + 1);
		fflush(stdout);
		return (NULL);
	}
	return (NULL);
}
