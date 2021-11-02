/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:09:30 by haseo             #+#    #+#             */
/*   Updated: 2021/11/03 01:36:48 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check(int i, t_philo *ph)
{
	int l;
	int r;

	l = LEFT(i, ph->info->num_philo);
	r = RIGHT(i, ph->info->num_philo);
	if (ph->state[i] == THINKING && \
		ph->state[l] != EATING && ph->state[r] != EATING)
	{
		ph->state[i] = EATING;
		pthread_mutex_unlock(&ph->philo[i]);
	}
}

int	pickup(t_philo *ph)
{
	int	time;

	pthread_mutex_lock(ph->check);
	ph->state[ph->id] = THINKING;
	check(ph->id, ph);
	pthread_mutex_unlock(ph->check);

	pthread_mutex_lock(&ph->philo[ph->id]);

	if (get_msec(&time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%d\t%d has taken a fork\n", time - ph->info->time_start, ph->id);
	return (0);
}

int	eating(t_philo *ph)
{
	int	time;

	if (get_msec(&time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));

	if (thread_msleep(ph->info->time_eat, time) == -1)
		return (ft_perror("[Error] thread_msleep\n", -1));

	if (get_msec(&time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%d\t%d is eating\n", time - ph->info->time_start, ph->id);

	return (0);
}

int	putdown(t_philo *ph)
{
	int	time;

	pthread_mutex_lock(ph->check);
	ph->state[ph->id] = SLEEPING;
	check(ph->left, ph);
	check(ph->right, ph);
	pthread_mutex_unlock(ph->check);

	if (get_msec(&time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%d\t%d has put a fork\n", time - ph->info->time_start, ph->id);
	return (0);
}

int	sleeping(t_philo *ph)
{
	int	time;

	if (get_msec(&time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
	if (thread_msleep(ph->info->time_sleep, time) == -1)
		return (ft_perror("[Error] thread_msleep\n", -1));

	if (get_msec(&time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%d\t%d is sleeping\n", time - ph->info->time_start, ph->id);

	return (0);
}

int	thinking(t_philo *ph)
{
	int	time;

	if (get_msec(&time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	printf("%d\t%d is thinking\n", time - ph->info->time_start, ph->id);
	return (0);
}
