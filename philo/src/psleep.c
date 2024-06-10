/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:37:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/10 20:27:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	pusleep(unsigned int total)
{
	struct timeval	t_start;
	struct timeval	t_curr;
	unsigned int	elapsed;

	elapsed = 0;
	if(gettimeofday(&t_start, NULL))
		error_exit(TIME_FAIL);
	printf("Sleep starting at %ld, %ld\n", t_start.tv_sec, t_start.tv_usec);
	while(elapsed < total)
	{
		if(gettimeofday(&t_curr, NULL))
			error_exit(TIME_FAIL);
		printf("Still sleeping at %ld, %ld\n", t_curr.tv_sec, t_curr.tv_usec);
		elapsed = (t_curr.tv_sec - t_start.tv_sec) * 1000000 + (t_curr.tv_usec - t_start.tv_usec);
		printf("useconds elapsed: %d of %d\n", elapsed, total);
		usleep(10000);
		printf("Remaining usecs: %d\n", total - elapsed);
		fflush(stdout);
		if ((int)(total - elapsed) < 100000)
		{
			printf("starting spinlock sleep\n");
			while (elapsed <= total)
			{
				if(gettimeofday(&t_curr, NULL))
					error_exit(TIME_FAIL);
				elapsed = (t_curr.tv_sec - t_start.tv_sec) * 1000000 + \
							 (t_curr.tv_usec - t_start.tv_usec);
				printf("%d\n", elapsed);
				if (elapsed >= total)
				{
					printf("Ending sleep at %d", total);
					sleep(5);
					return ;
				}
			}
		}
	}
}
