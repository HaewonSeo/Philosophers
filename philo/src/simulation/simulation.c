/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:06:25 by haseo             #+#    #+#             */
/*   Updated: 2021/11/16 13:58:16 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id & 1)
		if (thread_msleep((ph->info->time_eat / 2), ph->info->time_start) == -1)
			ft_perror("[Error] thread_msleep()\n", -1);
	while (1)
	{
		if (pickup(ph))
			break ;
		if (eating(ph))
			break ;
		if (putdown(ph))
			break ;
		if (sleeping(ph))
			break ;
		if (thinking(ph))
			break ;
	}
	if (pthread_mutex_unlock(&ph->mutex->simulation))
		ft_perror("[Error] pthread_mutex_unlock(simulation)\n", -1);
	return (NULL);
}

static void	*monitor(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (get_msec(&ph->time) == -1)
			ft_perror("[Error] get_msec()\n", -1);
		if (ph->time - ph->time_last_dine > (long int)ph->info->time_die)
			break ;
		if (thread_msleep(10, ph->time) == -1)
			ft_perror("[Error] thread_msleep()\n", -1);
	}
	if (print_state(ph, DIED))
		ft_perror("[Error] print_state()\n", -1);
	if (pthread_mutex_unlock(&ph->mutex->simulation))
		ft_perror("[Error] pthread_mutex_unlock(simulation)\n", -1);
	return (NULL);
}

int	simulation(t_philo *ph)
{
	int	i;

	if (pthread_mutex_lock(&ph->mutex->simulation))
		return (ft_perror("[Error] pthread_mutex_lock(simulation)\n", -1));
	if (get_msec(&ph->info->time_start) == -1)
		return (ft_perror("[Error] get_msec()\n", -1));
	i = -1;
	while (++i < ph->info->nr_philos)
	{
		ph[i].time_last_dine = ph->info->time_start;
		if (pthread_create(&ph[i].tid_dine, NULL, dine, (void *)&ph[i]))
			return (ft_perror("[Error] pthread_create(dine)\n", -1));
		if (pthread_detach(ph[i].tid_dine))
			return (ft_perror("[Error] pthread_detach(dine)\n", -1));
		if (pthread_create(&ph[i].tid_monitor, NULL, monitor, (void *)&ph[i]))
			return (ft_perror("[Error] pthread_create(monitor)\n", -1));
		if (pthread_detach(ph[i].tid_monitor))
			return (ft_perror("[Error] pthread_detach(monitor)\n", -1));
	}
	if (pthread_mutex_lock(&ph->mutex->simulation))
		return (ft_perror("[Error] pthread_mutex_lock(simulation)\n", -1));
	return (0);
}
