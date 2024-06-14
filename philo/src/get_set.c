/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:42:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/14 14:26:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_status(t_mutex *mtx, int *old, int newval)
{
	safe_mutex(mtx, LOCK);
	*old = newval;
	safe_mutex(mtx, UNLOCK);
}

int	get_phil_status(t_philo *philo)
{
	int out;

	out = 0;
	safe_mutex(&philo->mutex, LOCK);
	out = philo->status;
	safe_mutex(&philo->mutex, UNLOCK);
	return (out);
}

int	get_sim_status(t_table *table)
{
	int out;

	out = 0;
	safe_mutex(&table->mutex, LOCK);
	out = table->sim_status;
	safe_mutex(&table->mutex, UNLOCK);
	return (out);
}

int		get_int(t_mutex *mtx, int *val)
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

void	set_ts(t_mutex *mtx, t_timestamp *old, t_timestamp new)
{
	safe_mutex(mtx, LOCK);
	*old = new;
	safe_mutex(mtx, UNLOCK);
}

void	set_long(t_mutex *mtx, long *val, int newval)
{
	safe_mutex(mtx, LOCK);
	*val = newval;
	safe_mutex(mtx, UNLOCK);
}

int		get_long(t_mutex *mtx, long *val)
{
	long	out;

	out = 0;
	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
}

