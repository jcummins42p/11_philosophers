/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 18:20:23 by jcummins         ###   ########.fr       */
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
		safe_free(table, MALLOC_FAIL);
		exit (MALLOC_FAIL);
	}
	return (ret);
}

void	safe_free(t_table *table, t_errcode errcode)
{
	int	i;

	i = 0;
	printf(KGRN "Freeing allocated memory\n" KDEF);
	i = 0;
	if (errcode != BAD_ARGS && errcode != N_ARGS)
	{
		while (i < table->n_philos)
		{
			free(table->forks[i]);
			free(table->philos[i]);
			i++;
		}
		free(table->philos);
		free(table->forks);
	}
	free(table);
}

void	safe_mutex(t_mutex *mtx, t_mutex_code mutex_code)
{
	if (mutex_code == LOCK)
		pthread_mutex_lock(mtx);
	else if (mutex_code == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (mutex_code == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (mutex_code == DESTROY)
		pthread_mutex_destroy(mtx);
	else
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
		printf("%lld %d is thinking\n", ts / MSEC, philo->id + 1);
	else if (state == EATING)
		printf("%lld %d is eating\n", ts / MSEC, philo->id + 1);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", ts / MSEC, philo->id + 1);
	else if (state == FORKING)
	{
		if (state != DEAD)
			printf("%lld %d has taken a fork\n", ts / MSEC, philo->id + 1);
	}
	else if (state == DEAD)
		printf("%lld %d is dead\n", ts / MSEC, philo->id + 1);
	else if (state == DEBUG)
		printf("%lld %d finished eating\n", ts / MSEC, philo->id + 1);
	else if (state == LMT)
		printf("%lld %d last meal time %lld\n", ts / MSEC, philo->id + 1, philo->last_meal_time / MSEC);
	fflush(stdout);
}
