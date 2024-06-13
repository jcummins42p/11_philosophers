/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/13 14:05:49 by jcummins         ###   ########.fr       */
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
	while (i < table->n_philos)
		free(table->forks[i++]);
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
	(void) mtx;
	(void) mutex_code;
}

void	error_mutex(int status, t_mutex_code mutex_code)
{
	(void) status;
	(void) mutex_code;
}
