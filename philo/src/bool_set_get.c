/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_set_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:15:22 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 20:12:17 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mutex *mtx, bool *oldval, bool newval)
{
	pthread_mutex_lock(mtx);
	*oldval = newval;
	pthread_mutex_unlock(mtx);
}

bool	get_bool(t_mutex *mtx, bool *getval)
{
	bool	output;

	output = false;
	pthread_mutex_lock(mtx);
	output = *getval;
	pthread_mutex_unlock(mtx);
	return (output);
}
