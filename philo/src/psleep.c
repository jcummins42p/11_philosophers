/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:37:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/12 17:58:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_timestamp	ts_since_tv(struct timeval t_start)
{
	struct timeval	t_curr;
	t_timestamp		elapsed;

	if (gettimeofday(&t_curr, NULL))
		error_exit(TIME_FAIL);
	elapsed = (t_curr.tv_sec - t_start.tv_sec) * USEC + \
				(t_curr.tv_usec - t_start.tv_usec);
	return (elapsed);
}

t_timestamp	ts_since_ts(t_timestamp t_start, t_timestamp t_end)
{
	return (t_end - t_start);
}

t_timestamp	gettime(t_time_code time_code)
{
	struct timeval t_get;

	if (gettimeofday(&t_get, NULL))
		error_exit(TIME_FAIL);
	if (time_code == SEC)
		return (tv.tv_sec + (tv.tv_usec / USEC));
	else if (time_code == MLSEC)
		return ((tv.tv_sec * MSEC) + (tv.tv_usec / MSEC));
	else if (time_code == MUSEC)
		return ((tv.tv_sec * USEC) + tv.tv_usec);
	else
		error_exit(TIME_FAIL);
	return (1);
}

void	pusleep(t_timestamp total, t_table *table)
{
	t_timestamp	start;
	t_timestamp	elapsed;
	t_timestamp	rem;

	start = gettime(MSEC);
	while (gettime(MSEC) - start < total)
	{
		if (get_sim_status(table) != RUNNING)
			break;
		elapsed = gettime(MSEC) - start;
		rem = total - elapsed;

		if (rem > MSEC)
			esleep(total - MSEC);
		else
			while (gettime(MSEC) - start < total);
	}
}

/*void	pusleep(t_timestamp total)*/
/*{*/
	/*struct timeval	t_start;*/
	/*t_timestamp		elapsed;*/

	/*elapsed = 0;*/
	/*if (gettimeofday(&t_start, NULL))*/
		/*error_exit(TIME_FAIL);*/
	/*while (elapsed < total)*/
	/*{*/
		/*elapsed = ts_since_tv(t_start);*/
		/*if ((int)(total - elapsed) < MSEC)*/
		/*{*/
			/*while (elapsed <= total)*/
			/*{*/
				/*elapsed = ts_since_tv(t_start);*/
				/*if (elapsed >= total)*/
				/*{*/
					/*return ;*/
				/*}*/
			/*}*/
		/*}*/
		/*usleep((total - elapsed) >> 1);*/
	/*}*/
	/*return ;*/
/*}*/
