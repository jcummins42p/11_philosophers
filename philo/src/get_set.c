/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:42:43 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 16:40:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(t_mutex *mtx, int *val, int newval)
{
	safe_mutex(mtx, LOCK);
	*val = newval;
	safe_mutex(mtx, UNLOCK);
}

int		get_int(t_mutex *mtx, int *val)
{
	int	out;

	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
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

	safe_mutex(mtx, LOCK);
	out = *val;
	safe_mutex(mtx, UNLOCK);
	return (out);
}

