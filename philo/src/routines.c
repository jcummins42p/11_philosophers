/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/10 20:12:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_sleep(t_table *table, t_philo *philo)
{
	if (get_int(&philo->mutex, &philo->status) != DEAD)
	{
		set_status(&philo->mutex, &philo->status, SLEEPING);
		print_ts(table, philo, SLEEPING);
		pusleep(table->time_to_sleep);
		if (get_int(&philo->mutex, &philo->status) != DEAD)
		{
			if (get_int(&philo->mutex, &philo->n_meals) < table->n_limit_meals \
					|| table->n_limit_meals == 0)
				set_status(&philo->mutex, &philo->status, HUNGRY);
		}
	}
}

void	routine_eat(t_table *table, t_philo *philo)
{
	t_timestamp	eat_start;
	long		time_to_eat;

	time_to_eat = table->time_to_eat;
	if (get_int(&philo->mutex, &philo->status) == HUNGRY && \
			get_int(&table->mutex, &table->sim_status) == RUNNING)
	{
		set_status(&philo->mutex, &philo->status, EATING);
		eat_start = ts_since_tv(table->start_time);
		set_ts(&philo->mutex, &philo->last_meal_time, eat_start + time_to_eat);
		print_ts(table, philo, EATING);
		pusleep(table->time_to_eat);
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
		philo->r_fork = NULL;
		philo->l_fork = NULL;
		set_increment(&philo->mutex, &philo->n_meals);
		if (get_int(&philo->mutex, &philo->n_meals) == table->n_limit_meals)
			set_status(&philo->mutex, &philo->status, FULL);
		pusleep(200);
	}
	else
	{
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
	}
}

void	routine_cycle(t_table *table, t_philo *philo)
{
	int			t_status;
	int			p_status;

	/*t_status = get_int(&table->mutex, &table->sim_status);*/
	/*p_status = get_int(&philo->mutex, &philo->status);*/
	update_status(table, philo, &t_status, &p_status);
	/*if (p_status == THINKING)*/
		/*set_status(&philo->mutex, &philo->status, HUNGRY);*/
	/*else*/
		print_ts(table, philo, THINKING);
	if (p_status == HUNGRY && t_status == RUNNING)
		take_fork_one(table, philo);
	update_status(table, philo, &t_status, &p_status);
	if (p_status == HUNGRY && t_status == RUNNING)
		take_fork_two(table, philo);
	update_status(table, philo, &t_status, &p_status);
	if (philo->l_fork && philo->r_fork && t_status == RUNNING)
		routine_eat(table, philo);
	update_status(table, philo, &t_status, &p_status);
	if (p_status != DEAD && t_status == RUNNING)
		routine_sleep(table, philo);
}

void	synchronise_threads(t_table *table, t_philo *philo)
{
	t_timestamp	curr_time;

	set_ts(&philo->mutex, &philo->last_meal_time, table->starting_line);
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
}

void	*start_routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	/*printf("Commencing philosopher thread %d\n", philo->id);*/
	/*synchronise_threads(table, philo);*/
	/*pthread_barrier_wait(&table->start_barrier);*/
	safe_mutex(&table->mutex, LOCK);
	safe_mutex(&table->mutex, UNLOCK);
	if (philo->id % 2)
	{
		/*set_status(&philo->mutex, &philo->status, THINKING);*/
		/*print_ts(table, philo, THINKING);*/
		/*pusleep(table->time_to_sleep);*/
		routine_sleep(table, philo);
	}
	while (get_int(&philo->mutex, &philo->status) == HUNGRY && \
			get_int(&table->mutex, &table->sim_status) == RUNNING)
		routine_cycle(table, philo);
	if (get_int(&table->mutex, &table->sim_status) == RUNNING)
		print_ts(table, philo, THINKING);
	if (philo->r_fork)
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
	if (philo->l_fork)
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
	return (NULL);
}
