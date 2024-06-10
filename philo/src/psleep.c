/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:37:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/10 20:55:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

unsigned int	get_time_since(struct timeval t_start)
{
	struct timeval	t_curr;
	unsigned int	elapsed;

	if (gettimeofday(&t_curr, NULL))
		error_exit(TIME_FAIL);
	elapsed = (t_curr.tv_sec - t_start.tv_sec) * USEC + \
				(t_curr.tv_usec - t_start.tv_usec);
	return (elapsed);
}

void	pusleep(unsigned int total)
{
	struct timeval	t_start;
	unsigned int	elapsed;

	elapsed = 0;
	if (gettimeofday(&t_start, NULL))
		error_exit(TIME_FAIL);
	while (elapsed < total)
	{
		elapsed = get_time_since(t_start);
		printf("%d elapsed in current sleep\n", elapsed);
		if ((int)(total - elapsed) < 500)
		{
			while (elapsed <= total)
			{
				elapsed = get_time_since(t_start);
				if (elapsed >= total)
				{
					printf("Slept %d and returning\n", elapsed);
					return ;
				}
			}
		}
		usleep((total - elapsed) >> 1);
	}
}
