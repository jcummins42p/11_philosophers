/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 19:30:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes, t_table *table)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		printf("Malloc error\n");
		safe_free(table);
		exit (MALLOC_FAIL);
	}
	return (ret);
}

void	safe_free(t_table *table)
{
	int	i;

	i = 0;
	printf(KGRN "Freeing allocated memory\n" KDEF);
	i = 0;
	while (i < table->n_philos)
	{
		free(table->forks[i]);
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
	free(table->forks);
}

void	safe_mutex(t_mutex *mtx, t_mutex_code mutex_code)
{
	int	errcode;

	errcode = 0;
	if (mutex_code == LOCK)
		errcode = pthread_mutex_lock(mtx);
	else if (mutex_code == UNLOCK)
		errcode = pthread_mutex_unlock(mtx);
	if (errcode)
		error_exit(MUTEX_FAIL);
}

void	error_mutex(int status, t_mutex_code mutex_code)
{
	(void) status;
	(void) mutex_code;
}

void	print_ts(t_table *table, t_philo *philo, int state)
{
	t_timestamp	ts;

	ts = ts_since_tv(table->start_time);
	if (state == THINKING)
		printf("%d %d is thinking\n", ts / MSEC, philo->id + 1);
	else if (state == EATING)
		printf("%d %d is eating\n", ts / MSEC, philo->id + 1);
	else if (state == SLEEPING)
		printf("%d %d is sleeping\n", ts / MSEC, philo->id + 1);
	else if (state == FORKING)
	{
		if (state != DEAD)
			printf("%d %d has taken a fork\n", ts / MSEC, philo->id + 1);
	}
	else if (state == DEAD)
		printf("%d %d is dead\n", ts / MSEC, philo->id + 1);
	else if (state == DEBUG)
		printf("%d %d finished eating\n", ts / MSEC, philo->id + 1);
	fflush(stdout);
}
