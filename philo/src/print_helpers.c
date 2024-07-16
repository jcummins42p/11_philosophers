/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:28:16 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 20:18:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(char *str, t_table *table)
{
	pthread_mutex_lock(&table->printf_mutex);
	printf("%s", str);
	pthread_mutex_unlock(&table->printf_mutex);
}

void	print_ts(t_table *table, t_philo *philo, int state)
{
	t_timestamp	ts;

	pthread_mutex_lock(&table->printf_mutex);
	ts = ts_since_tv(table->start_time);
	if (state == THINKING)
		printf("%lld %d is thinking\n", ts / MSEC, philo->id + 1);
	else if (state == EATING)
		printf("%lld %d is eating\n", ts / MSEC, philo->id + 1);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", ts / MSEC, philo->id + 1);
	else if (state == FORKING)
	{
		if (state != DEAD)
			printf("%lld %d has taken a fork\n", ts / MSEC, philo->id + 1);
	}
	else if (state == DEAD)
		printf("%lld %d is dead\n", ts / MSEC, philo->id + 1);
	fflush(stdout);
	pthread_mutex_unlock(&table->printf_mutex);
}
