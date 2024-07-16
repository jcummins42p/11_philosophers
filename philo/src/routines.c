/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 15:07:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_sleep(t_table *table, t_philo *philo)
{
	int status;

	status = get_phil_status(philo);
	if (status != DEAD)
	{
		print_ts(table, philo, SLEEPING);
		set_status(&philo->mutex, &philo->status, SLEEPING);
		psleep(table->time_to_sleep, table);
		status = get_phil_status(philo);
		if (status != DEAD)
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

	set_status(&philo->mutex, &philo->status, EATING);
	time_to_eat = table->time_to_eat;
	if (get_int(&table->mutex, &table->sim_status) == RUNNING)
	{
		eat_start = ts_since_tv(table->start_time);
		set_ts(&philo->mutex, &philo->last_meal_time, eat_start);
		print_ts(table, philo, EATING);
		psleep(table->time_to_eat, table);
		print_ts(table, philo, DEBUG);
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
		philo->r_fork = NULL;
		philo->l_fork = NULL;
		set_increment(&philo->mutex, &philo->n_meals);
		if (get_int(&philo->mutex, &philo->n_meals) == table->n_limit_meals)
			set_status(&philo->mutex, &philo->status, FULL);
		psleep(200, table);
	}
	else
	{
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
		philo->r_fork = NULL;
		philo->l_fork = NULL;
	}
}

void	routine_cycle(t_table *table, t_philo *philo)
{
	int			t_status;
	int			p_status;

	update_status(table, philo, &t_status, &p_status);
	print_ts(table, philo, THINKING);
	if (p_status == HUNGRY && t_status == RUNNING)
	{
		print_ts(table, philo, FORKING);
		take_fork_one(table, philo);
	}
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

//	the odd numbered philos need to sleep first so that the even ones can eat
//	the first philo delays starting so that for odd n_philos they think first
//	this avoids the chain of thinking going through the higher numbered philos,
//	who start later and are more prone to dying
void	*start_routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (get_sim_status(table) == WAITING)
		;
	print_ts(table, philo, THINKING);
	if (philo->id % 2)
		routine_sleep(table, philo);
	else if (philo->id == 0)
		psleep(200, table);
	if (gettimeofday(&philo->start_time, NULL))
		error_exit(TIME_FAIL);
	while (get_phil_status(philo) == HUNGRY && get_sim_status(table) == RUNNING)
		routine_cycle(table, philo);
	if (get_sim_status(table) == RUNNING)
		print_ts(table, philo, THINKING);
	if (philo->r_fork)
		safe_mutex(&philo->r_fork->mutex, UNLOCK);
	if (philo->l_fork)
		safe_mutex(&philo->l_fork->mutex, UNLOCK);
	return (NULL);
}
/*void	synchronise(t_table *table, t_philo *philo)*/
/*{*/
	/*t_timestamp	delay;*/

	/*(void)philo;*/
	/*safe_mutex(&table->mutex, LOCK);*/
	/*safe_mutex(&table->mutex, UNLOCK);*/
	/*delay = ts_since_tv(table->start_time);*/
	/*[>printf("Delay starting philo %d was %u\n", philo->id, delay);<]*/
	/*psleep((MSEC * 100) - delay, table);*/
	/*[>set_ts(&philo->mutex, &philo->start_time, gettime(MUSEC));<]*/
	/*[>delay = ts_since_tv(table->start_time);<]*/
	/*[>printf("Adjusted delay starting philo %d was %lld\n", philo->id, delay);<]*/
	/*[>fflush(stdout);<]*/
/*}*/
