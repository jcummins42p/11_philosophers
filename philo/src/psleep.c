/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:37:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/20 00:50:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned int	ts_since_tv(struct timeval t_start)
{
	struct timeval	t_curr;
	t_timestamp		elapsed;

	if (gettimeofday(&t_curr, NULL))
		error_exit(TIME_FAIL);
	elapsed = (t_curr.tv_sec - t_start.tv_sec) * USEC + \
				(t_curr.tv_usec - t_start.tv_usec);
	return (elapsed);
}

unsigned int	ts_since_ts(t_timestamp t_start, t_timestamp t_end)
{
	return (t_end - t_start);
}

void	pusleep(unsigned int total)
{
	struct timeval	t_start;
	t_timestamp		elapsed;

	elapsed = 0;
	if (gettimeofday(&t_start, NULL))
		error_exit(TIME_FAIL);
	while (elapsed < total)
	{
		elapsed = ts_since_tv(t_start);
		if ((int)(total - elapsed) < MSEC)
		{
			while (elapsed <= total)
			{
				elapsed = ts_since_tv(t_start);
				if (elapsed >= total)
				{
					return ;
				}
			}
		}
		usleep((total - elapsed) >> 1);
	}
}
