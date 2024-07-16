/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 15:35:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_sim_status(t_table *table, int newval)
{
	pthread_mutex_lock(&table->mutex);
	*table->sim_status = newval;
	pthread_mutex_lock(&table->mutex);
}

void	set_phil_status(t_philo *philo, int newval)
{
	pthread_mutex_lock(&philo->mutex);
	*philo->status = newval;
	pthread_mutex_unlock(&philo->mutex);
}

void	set_ts(t_mutex *mtx, t_timestamp *old, t_timestamp new)
{
	safe_mutex(mtx, LOCK);
	*old = new;
	safe_mutex(mtx, UNLOCK);
}

void	set_increment(t_mutex *mtx, int *old)
{
	safe_mutex(mtx, LOCK);
	(*old)++;
	safe_mutex(mtx, UNLOCK);
}

void	set_decrement(t_mutex *mtx, int *old)
{
	safe_mutex(mtx, LOCK);
	(*old)--;
	safe_mutex(mtx, UNLOCK);
}
