/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:06:25 by haseo             #+#    #+#             */
/*   Updated: 2021/11/07 23:20:01 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *ph)
{
	if (get_msec(&ph->time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%ldms\t"CYN"%d is thinking\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	return (0);
}

void	*dine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ph->time_last_dine = ph->info->time_start;
	while (1)
	{
		if (pickup(ph) == -1)
			break;
		if (eating(ph) == -1)
			break;
		if (putdown(ph) == -1)
			break;
		if (sleeping(ph) == -1)
			break;
		if (thinking(ph) == -1)
			break;
	}
	if (get_msec(&ph->time) == -1)
		ft_perror("[Error] get_msec\n", -1);
	printf("%ldms\t"RED"%d died\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*ph;
	long int	time;

	ph = (t_philo *)arg;
	if (get_msec(&time) == -1)
		ft_perror("[Error] get_msec\n", -1);
	if (thread_msleep(ph->info->time_die - 10, time) == -1)
		ft_perror("[Error] thread_msleep\n", -1);
	while (1)
	{
		if (get_msec(&time) == -1)
			ft_perror("[Error] get_msec\n", -1);
		if (time - ph->time_last_dine > (long int)ph->info->time_die)
		{
			printf("[%d]\t%ld - %ld = %ld\n", ph->id + 1, time, ph->time_last_dine, time-ph->time_last_dine);
			printf("************\n");
			printf("%ldms\t"RED"%d died\n"EOC, time - ph->info->time_start, ph->id + 1);
			if (pthread_mutex_unlock(&ph->mutex->simulation))
				ft_perror("[Error] pthread_mutex_unlock simulation\n", -1);
			break;
		}
	}
	return (NULL);
}

int threading(t_philo *ph)
{
	int	i;

	if (get_msec(&ph->info->time_start) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	i = -1;
	while (++i < ph->info->num_philo)
	{
		if (pthread_create(&ph[i].tid_dine, NULL, (void *)dine, (void *)&ph[i]))
			return (ft_perror("[Error] pthread_create\n", -1));
		if (pthread_detach(ph[i].tid_dine))
			return (ft_perror("[Error] pthread_detach\n", -1));
		if (pthread_create(&ph[i].tid_monitor, NULL, (void *)monitor, (void *)&ph[i]))
			return (ft_perror("[Error] pthread_create\n", -1));
		if (pthread_detach(ph[i].tid_monitor))
			return (ft_perror("[Error] pthread_detach\n", -1));
	}
	if (pthread_mutex_lock(&ph->mutex->simulation))
		return (ft_perror("[Error] pthread_mutex_lock simulation\n", -1));
	// i = -1;
	// while (++i < ph->info->num_philo)
	// {
		// if (pthread_join(ph[i].tid_dine, NULL))
			// return (ft_perror("[Error] pthread_join dine\n", -1));
		// if (pthread_join(ph[i].tid_monitor, NULL))
			// return (ft_perror("[Error] pthread_join monitor\n", -1));
	// }
	return (0);
}
