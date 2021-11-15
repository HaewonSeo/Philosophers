/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:09:30 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 16:16:55 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->mutex->fork[ph->l]))
		return (ft_perror("[Error] pthread_mutex_lock fork[l]\n", -1));
	if (print_state(ph, TAKEN))
		return (ft_perror("[Error] print state\n", -1));
	if (pthread_mutex_lock(&ph->mutex->fork[ph->r]))
		return (ft_perror("[Error] pthread_mutex_lock fork[r]\n", -1));
	if (print_state(ph, TAKEN))
		return (ft_perror("[Error] print state\n", -1));
	return (0);
}

int	eating(t_philo *ph)
{
	if (print_state(ph, EATING))
		return (ft_perror("[Error] print_state()\n", -1));
	if (get_msec(&ph->time_last_dine) == -1)
		return (ft_perror("[Error] get_msec()\n", -1));
	if (thread_msleep(ph->info->time_eat, ph->time_last_dine) == -1)
		return (ft_perror("[Error] thread_msleep()\n", -1));
	return (0);
}

int	putdown(t_philo *ph)
{
	if (pthread_mutex_unlock(&ph->mutex->fork[ph->l]))
		return (ft_perror("[Error] pthread_mutex_unlock(fork[l])\n", -1));
	if (pthread_mutex_unlock(&ph->mutex->fork[ph->r]))
		return (ft_perror("[Error] pthread_mutex_unlock(fork[r])\n", -1));
	++(ph->nr_dininig);
	if (ph->nr_dininig == ph->info->nr_must_eat)
		++(ph->info->nr_end_dine);
	if (ph->info->nr_end_dine == ph->info->nr_philos)
	{
		if (ph->nr_dininig == ph->info->nr_must_eat)
		{
			if (print_state(ph, COMPLETE))
				return (ft_perror("[Error] print_state()\n", -1));
			if (pthread_mutex_unlock(&ph->mutex->simulation))
				return (ft_perror("[Error] pthread_mutex_unlock(simul)\n", -1));
		}
		return (-1);
	}
	return (0);
}

int	sleeping(t_philo *ph)
{
	if (print_state(ph, SLEEPING))
		return (ft_perror("[Error] print_state()\n", -1));
	if (thread_msleep(ph->info->time_sleep, ph->time) == -1)
		return (ft_perror("[Error] thread_msleep()\n", -1));
	return (0);
}

int	thinking(t_philo *ph)
{
	if (print_state(ph, THINKING))
		return (ft_perror("[Error] print_state()\n", -1));
	return (0);
}
