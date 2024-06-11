/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/11 20:18:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *take_left_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;

	target = philo->id;
	out = take_fork(table, table->forks[target], philo);
	return (out);
}

void *take_right_fork(t_table *table, t_philo *philo)
{
	int 		target;
	pthread_t	*out;

	target = (philo->id + 1) % table->n_philos;
	out = take_fork(table, table->forks[target], philo);
	return (out);
}

void *take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->id == philo->id)
	{
		philo->l_fork = fork;
		printf("Philo %d has taken the fork to their LEFT\n", philo->id);
	}
	else if (fork->id == (philo->id + 1) % table->n_philos)
	{
		philo->r_fork = fork;
		printf("Philo %d has taken the fork to their RIGHT\n", philo->id);
	}
	else
		printf("Philo %d got A FORBIDDEN FORK (%d)\n", philo->id, fork->id);
	pthread_mutex_unlock(&fork->mutex);
	return (NULL);
}

void	*routine_sleep(t_table *table, t_philo *philo)
{
	t_timestamp	sleep_start;

	sleep_start = get_time_since(table->start_time);
	philo->status = SLEEPING;
	printf("%d %d SLEEPING\n", sleep_start, philo->id);
	pusleep(table->time_to_sleep);
	return (NULL);
}

void	*routine_eat(t_table *table, t_philo *philo)
{
	t_timestamp	eat_start;

	eat_start = get_time_since(table->start_time);
	philo->status = EATING;
	printf("%d %d EATING\n", eat_start, philo->id);
	pusleep(table->time_to_eat);
	philo->n_meals += 1;
	if (philo->n_meals == table->n_limit_meals)
		philo->full = true;
	return(NULL);
}

void	*routine_run(t_table *table, t_philo *philo)
{
	while (philo->full == false)
	{
		routine_sleep(table, philo);
		routine_eat(table, philo);
	}
	if (philo->full == true)
	printf("Philo %d is full\n", philo->id);
	return (NULL);
}
