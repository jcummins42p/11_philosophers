/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:46:04 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 19:02:05 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	return (ret);
}

void	safe_mutex(t_mtx *mutex, t_mutex_code mutex_code)
{
	(void) mutex;
	(void) mutex_code;
}

void	error_mutex(int status, t_mutex_code mutex_code)
{
	(void) status;
	(void) mutex_code;
}
