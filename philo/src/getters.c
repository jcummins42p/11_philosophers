/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 15:34:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_phil_status(t_philo *philo)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&philo->mutex);
	out = philo->status;
	pthread_mutex_unlock(&philo->mutex);
	return (out);
}

int	get_sim_status(t_table *table)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&table->mutex);
	out = table->sim_status;
	pthread_mutex_unlock(&table->mutex);
	return (out);
}

int	get_int(t_mutex *mtx, int *val)
{
	int	out;

	out = 0;
	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
}

t_timestamp	get_ts(t_mutex *mtx, t_timestamp *val)
{
	t_timestamp	out;

	out = 0;
	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
}

int	get_long(t_mutex *mtx, long *val)
{
	long	out;

	out = 0;
	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
}
