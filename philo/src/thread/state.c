/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:09:30 by haseo             #+#    #+#             */
/*   Updated: 2021/11/07 23:14:46 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(int i, t_philo *ph)
{
	int l;
	int r;

	l = i;
	r = RIGHT(i, ph->info->num_philo);
	if (ph->fork[l] == USABLE && ph->fork[r] == USABLE)
	{
		ph->fork[l] = UNUSABLE;
		ph->fork[r] = UNUSABLE;
		if (pthread_mutex_unlock(&ph->mutex->philo[i]))
			return (ft_perror("[Error] pthread_mutex_unlock philo_mutex\n", -1));
	}
	return (0);
}

int	pickup(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->mutex->check))
		return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
	if (check(ph->id, ph) == -1)
		return (ft_perror("[Error] check philo\n", -1));
	if (pthread_mutex_unlock(&ph->mutex->check))
		return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));
	if (pthread_mutex_lock(&ph->mutex->philo[ph->id]))
		return (ft_perror("[Error] pthread_mutex_lock philo\n", -1));

	if (get_msec(&ph->time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	return (0);
}

int	eating(t_philo *ph)
{
	if (get_msec(&ph->time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%ldms\t"YEL"%d is eating\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	if (thread_msleep(ph->info->time_eat, ph->time) == -1)
		return (ft_perror("[Error] thread_msleep\n", -1));

	if (get_msec(&ph->time_last_dine) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	return (0);
}

int	putdown(t_philo *ph)
{
	int	l;
	int	r;

	l = ph->id;
	r = RIGHT(ph->id, ph->info->num_philo);
	if (pthread_mutex_lock(&ph->mutex->check))
		return (ft_perror("[Error] pthread_mutex_lock check in putdown\n", -1));
	ph->fork[l] = USABLE;
	ph->fork[r] = USABLE;
	if (check(ph->left, ph) == -1)
		return (ft_perror("[Error] check left_philo\n", -1));
	if (check(ph->right, ph) == -1)
		return (ft_perror("[Error] check right_philo\n", -1));
	if (pthread_mutex_unlock(&ph->mutex->check))
		return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));

	++(ph->num_dine);
	if (ph->num_dine == ph->info->num_must_eat)
		++(ph->info->num_end_dine);
	if (ph->info->num_end_dine == ph->info->num_philo)
	{
		if (ph->num_dine == ph->info->num_must_eat)
		{
			printf("[%d] eat %d dine --- num_must_eat=%d, num_end_dine=%d\n", ph->id + 1, ph->num_dine, ph->info->num_must_eat, ph->info->num_end_dine);
			if (pthread_mutex_unlock(&ph->mutex->simulation))
				return (ft_perror("[Error] pthread_mutex_unlock simulation\n", -1));
		}
		return (-1);
	}
	return (0);
}

int	sleeping(t_philo *ph)
{
	if (get_msec(&ph->time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
	printf("%ldms\t"MAG"%d is sleeping\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	if (thread_msleep(ph->info->time_sleep, ph->time) == -1)
		return (ft_perror("[Error] thread_msleep\n", -1));
	return (0);
}
