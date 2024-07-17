/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/17 13:48:10 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_sleep(t_table *table, t_philo *philo)
{
	int	status;

	status = get_philo_status(philo);
	if (status != DEAD)
	{
		print_ts(table, philo, SLEEPING);
		set_philo_status(philo, SLEEPING);
		psleep(table->time_to_sleep, table);
		status = get_philo_status(philo);
		if (status != DEAD)
			set_philo_status(philo, HUNGRY);
	}
}

void	routine_eat(t_table *table, t_philo *philo)
{
	t_timestamp	eat_start;
	long		time_to_eat;

	set_philo_status(philo, EATING);
	time_to_eat = table->time_to_eat;
	if (get_sim_status(table) == RUNNING)
	{
		eat_start = ts_since_tv(table->start_time);
		set_ts(&philo->mutex, &philo->last_meal_time, eat_start);
		print_ts(table, philo, EATING);
		psleep(table->time_to_eat, table);
		drop_both_forks(philo);
		set_increment(&philo->mutex, &philo->n_meals);
	}
	else
		drop_both_forks(philo);
}

void	routine_cycle(t_table *table, t_philo *philo)
{
	int			t_status;
	int			p_status;

	update_status(table, philo, &t_status, &p_status);
	print_ts(table, philo, THINKING);
	if (p_status == HUNGRY && t_status == RUNNING)
		take_fork_one(table, philo);
	update_status(table, philo, &t_status, &p_status);
	if (table->n_philos != 1)
	{
		if (p_status == HUNGRY && t_status == RUNNING)
			take_fork_two(table, philo);
		update_status(table, philo, &t_status, &p_status);
		if (philo->l_fork && philo->r_fork && t_status == RUNNING)
			routine_eat(table, philo);
		update_status(table, philo, &t_status, &p_status);
		if (p_status != DEAD && t_status == RUNNING)
			routine_sleep(table, philo);
		psleep(200, table);
	}
	else
		while (get_sim_status(table) == RUNNING)
			;
}

//	the odd numbered philos need to sleep first so that the even ones can eat
//	the first philo delays starting so that for odd n_philos they think first
//	this avoids the chain of thinking going through the higher numbered philos,
//	who start later and are more prone to dying
void	*start_routine(void *arg)
{
	t_philo		*phil;
	t_table		*table;

	phil = (t_philo *)arg;
	table = phil->table;
	while (get_sim_status(table) == WAITING)
		psleep(100, table);
	if (phil->id % 2)
		routine_sleep(table, phil);
	else if (phil->id == 0)
		psleep(200, table);
	pthread_mutex_lock(&phil->mutex);
	if (gettimeofday(&phil->start_time, NULL))
		error_exit(TIME_FAIL);
	pthread_mutex_unlock(&phil->mutex);
	while (get_philo_status(phil) == HUNGRY && get_sim_status(table) == RUNNING)
		routine_cycle(table, phil);
	if (phil->r_fork)
		safe_mutex(&phil->r_fork->mutex, UNLOCK);
	if (phil->l_fork)
		safe_mutex(&phil->l_fork->mutex, UNLOCK);
	return (NULL);
}
