/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/13 18:13:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*take_left_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;
	t_timestamp	lfork_start;

	lfork_start = ts_since_tv(table->start_time);
	printf("%-10d %-4d taking left fork\n", lfork_start / MSEC, philo->id + 1);
	fflush(stdout);
	target = philo->id;
	out = take_fork(table, table->forks[target], philo);
	lfork_start = ts_since_tv(table->start_time);
	printf("%-10d %-4d taken left fork (%d)\n", lfork_start / MSEC, philo->id + 1, philo->l_fork->id);
	fflush(stdout);
	return (out);
}

void	*take_right_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;
	t_timestamp	rfork_start;

	rfork_start = ts_since_tv(table->start_time);
	printf("%-10d %-4d taking right fork\n", rfork_start / MSEC, philo->id + 1);
	fflush(stdout);
	target = (philo->id + 1) % table->n_philos;
	out = take_fork(table, table->forks[target], philo);
	rfork_start = ts_since_tv(table->start_time);
	printf("%-10d %-4d taken right fork (%d)\n", rfork_start / MSEC, philo->id + 1, philo->r_fork->id);
	fflush(stdout);
	return (out);
}

void	*take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex);
	if (philo->status == DEAD)
		printf("Philo %d died while waiting for FORK (%d)\n", philo->id + 1, fork->id);
	else
	{
		if (fork->id == philo->id)
			philo->l_fork = fork;
		else if (fork->id == (philo->id + 1) % table->n_philos)
			philo->r_fork = fork;
		else
			printf("Philo %d got A FORBIDDEN FORK (%d)\n", philo->id + 1, fork->id);
	}
	return (NULL);
}

void	*routine_sleep(t_table *table, t_philo *philo)
{
	t_timestamp	sleep_start;

	sleep_start = ts_since_tv(table->start_time);
	if (get_int(&philo->mutex, &philo->status) != DEAD)
	{
		set_status(&philo->mutex, &philo->status, SLEEPING);
		printf("%-10d %-4d SLEEPING\n", sleep_start / MSEC, philo->id + 1);
		fflush(stdout);
		pusleep(table->time_to_sleep);
		if (get_int(&philo->mutex, &philo->status) != DEAD)
			set_status(&philo->mutex, &philo->status, HUNGRY);
	}
	return (NULL);
}

void	*routine_eat(t_table *table, t_philo *philo)
{
	t_timestamp	eat_start;

	if (philo->status == HUNGRY)
	{
		set_status(&philo->mutex, &philo->status, EATING);
		eat_start = ts_since_tv(table->start_time);
		philo->last_meal_time = eat_start + table->time_to_eat;
		/*printf("%-10d %-4d EATING meal %d of %d\n", eat_start, philo->id + 1, philo->n_meals + 1, table->n_limit_meals);*/
		printf("%-10d %-4d EATING\n", eat_start / MSEC, philo->id + 1);
		fflush(stdout);
		pusleep(table->time_to_eat - 4);
		philo->n_meals += 1;
		pthread_mutex_unlock(&philo->l_fork->mutex);
		philo->l_fork = NULL;
		pthread_mutex_unlock(&philo->r_fork->mutex);
		philo->r_fork = NULL;
		if (philo->n_meals == table->n_limit_meals)
			set_status(&philo->mutex, &philo->status, FULL);
	}
	return (NULL);
}

void	*routine_run(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	t_timestamp	curr_time;

	philo = (t_philo *)arg;
	table = philo->table;
	philo->last_meal_time = table->starting_line;
	/*printf("Setting philo %d last meal time to %d\n", philo->id, philo->last_meal_time);*/
	curr_time = ts_since_tv(table->start_time);
	pusleep(table->starting_line - curr_time);
	curr_time = ts_since_tv(table->start_time);
	/*printf("Starting philo %d at %d\n", philo->id + 1, curr_time);*/
	/*fflush(stdout);*/
	if (philo->id % 2)
		routine_sleep(table, philo);
	while (philo->status == HUNGRY && philo->table->sim_status == RUNNING)
	{
		if (philo->status == HUNGRY && table->sim_status == RUNNING)
			take_left_fork(table, philo);
		if (philo->status == HUNGRY && table->sim_status == RUNNING)
			take_right_fork(table, philo);
		if (philo->l_fork && philo->r_fork && philo->status == HUNGRY)
			routine_eat(table, philo);
		if (philo->status != FULL)
			routine_sleep(table, philo);
	}
	return (NULL);
}
