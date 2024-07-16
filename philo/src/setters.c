/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 18:19:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_sim_status(t_table *table, int newval)
{
	pthread_mutex_lock(&table->mutex);
	table->sim_status = newval;
	pthread_mutex_unlock(&table->mutex);
}

void	set_philo_status(t_philo *philo, int newval)
{
	pthread_mutex_lock(&philo->mutex);
	philo->status = newval;
	pthread_mutex_unlock(&philo->mutex);
}

void	set_ts(t_mutex *mtx, t_timestamp *old, t_timestamp new)
{
	pthread_mutex_lock(mtx);
	*old = new;
	pthread_mutex_unlock(mtx);
}

void	set_increment(t_mutex *mtx, int *old)
{
	pthread_mutex_lock(mtx);
	(*old)++;
	pthread_mutex_unlock(mtx);
}

void	set_decrement(t_mutex *mtx, int *old)
{
	pthread_mutex_lock(mtx);
	(*old)--;
	pthread_mutex_unlock(mtx);
}
