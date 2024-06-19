/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:07:49 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/19 20:24:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	update_status(t_table *table, t_philo *philo, int *t, int *p)
{
	*t = get_int(&table->mutex, &table->sim_status);
	*p = get_int(&philo->mutex, &philo->status);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	long	out;
	int		i;

	i = 0;
	out = 0;
	while (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (out)
				return (out);
			else
				return (-1);
		}
		out = (out * 10) + (str[i++] - '0');
		if (out > INT_MAX)
			return (-1);
	}
	return (out);
}
