/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:09:30 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 23:05:03 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pickup(t_philo *ph)
{
	if (sem_wait(ph->sem->forks) == -1)
		return (ft_perror("[Error] sem_wait(forks)\n", -1));
	if (print_state(ph, TAKEN))
		return (ft_perror("[Error] print state\n", -1));
	if (sem_wait(ph->sem->forks) == -1)
		return (ft_perror("[Error] sem_wait(forks)\n", -1));
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
	++(ph->nr_dininig);
	if (ph->nr_dininig == ph->info->nr_must_eat)
		if (sem_post(ph->sem->complete) == -1)
			return (ft_perror("[Error] sem_post(complete)\n", -1));
	return (0);
}

int	putdown(t_philo *ph)
{
	if (sem_post(ph->sem->forks) == -1)
		return (ft_perror("[Error] sem_post(forks)\n", -1));
	if (sem_post(ph->sem->forks) == -1)
		return (ft_perror("[Error] sem_post(forks)\n", -1));
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
