/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/20 00:04:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_phil_status(t_philo *philo)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&philo->mutex);
	/*safe_mutex(&philo->mutex, LOCK);*/
	out = philo->status;
	pthread_mutex_unlock(&philo->mutex);
	/*safe_mutex(&philo->mutex, UNLOCK);*/
	return (out);
}

int	get_sim_status(t_table *table)
{
	int	out;

	out = 0;
	/*safe_mutex(&table->mutex, LOCK);*/
	pthread_mutex_lock(&table->mutex);
	out = table->sim_status;
	pthread_mutex_unlock(&table->mutex);
	/*safe_mutex(&table->mutex, UNLOCK);*/
	return (out);
}

int	get_int(t_mutex *mtx, int *val)
{
	int	out;

	out = 0;
	/*safe_mutex(mtx, LOCK);*/
	pthread_mutex_lock(mtx);
	out = *val;
	pthread_mutex_unlock(mtx);
	/*safe_mutex(mtx, UNLOCK);*/
	return (out);
}

t_timestamp	get_ts(t_mutex *mtx, t_timestamp *val)
{
	t_timestamp	out;

	out = 0;
	/*safe_mutex(mtx, LOCK);*/
	pthread_mutex_lock(mtx);
	out = *val;
	pthread_mutex_unlock(mtx);
	/*safe_mutex(mtx, UNLOCK);*/
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
