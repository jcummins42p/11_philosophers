/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 17:04:52 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_phil_status(t_philo *philo)
{
	int	out;

	out = 0;
	safe_mutex(&philo->mutex, LOCK);
	out = philo->status;
	safe_mutex(&philo->mutex, UNLOCK);
	return (out);
}

int	get_sim_status(t_table *table)
{
	int	out;

	out = 0;
	safe_mutex(&table->mutex, LOCK);
	out = table->sim_status;
	safe_mutex(&table->mutex, UNLOCK);
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
