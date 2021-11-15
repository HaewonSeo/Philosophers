/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:06:21 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 16:13:54 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_msec(long int *msec)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (ft_perror("[Error] gettimeofday\n", -1));
	*msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	thread_msleep(long int msec, long int time_start)
{
	long int	time;

	while (1)
	{
		if (get_msec(&time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		if (time - time_start >= msec)
			break ;
		if (usleep(10) == -1)
			return (ft_perror("[Error] usleep\n", -1));
	}
	return (0);
}
