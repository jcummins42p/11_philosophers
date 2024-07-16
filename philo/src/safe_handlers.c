/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 19:40:05 by jcummins         ###   ########.fr       */
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
	if (errcode != BAD_ARGS && errcode != N_ARGS)
	{
		while (i < table->n_philos)
		{
			pthread_mutex_destroy(&table->philos[i]->mutex);
			pthread_mutex_destroy(&table->forks[i]->mutex);
			free(table->forks[i]);
			free(table->philos[i]);
			i++;
		}
		pthread_mutex_destroy(&table->mutex);
		pthread_mutex_destroy(&table->printf_mutex);
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
