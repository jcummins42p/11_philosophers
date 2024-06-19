/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:35 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/19 11:14:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_status(t_mutex *mtx, int *old, int newval)
{
	safe_mutex(mtx, LOCK);
	*old = newval;
	safe_mutex(mtx, UNLOCK);
}

void	set_increment(t_mutex *mtx, int *old)
{
	safe_mutex(mtx, LOCK);
	*old = *old + 1;
	safe_mutex(mtx, UNLOCK);
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
