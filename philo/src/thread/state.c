/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:09:30 by haseo             #+#    #+#             */
/*   Updated: 2021/11/10 00:58:52 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(int i, t_philo *ph)
{
	int l;
	int r;

	l = i;
	r = RIGHT(i, ph->info->nr_philos);
	if (ph->fork[l] == USABLE && ph->fork[r] == USABLE)
	{
		// ph->fork[l] = UNUSABLE;
		// ph->fork[r] = UNUSABLE;
		return 1;
		// printf("[%d] pthread_mutex_unlock\n", i + 1);
		// if (pthread_mutex_unlock(&ph->mutex->philo[i]))
			// return (ft_perror("[Error] pthread_mutex_unlock philo_mutex\n", -1));
	}
	return (0);
}

int	pickup(t_philo *ph)
{
	int	l;
	int	r;

	l = ph->id;
	r = RIGHT(ph->id, ph->info->nr_philos);
	if (ph->id & 1)
	{
		if (pthread_mutex_lock(&ph->mutex->philo[l]))
			return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
		if (get_msec(&ph->time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
		if (pthread_mutex_lock(&ph->mutex->philo[r]))
			return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
		if (get_msec(&ph->time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	}
	else
	{
		if (pthread_mutex_lock(&ph->mutex->philo[r]))
			return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
		if (get_msec(&ph->time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
		if (pthread_mutex_lock(&ph->mutex->philo[l]))
			return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
		if (get_msec(&ph->time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	}

	// while (1)
	// {
		// if (pthread_mutex_lock(&ph->mutex->check))
			// return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
		// if (check(ph->id, ph))
			// break;
		// int ch = check(ph->id, ph);
		// if (ch)
			// break;
		// if (check(ph->id, ph) == -1)
		// 	return (ft_perror("[Error] check philo\n", -1));
		// if (pthread_mutex_unlock(&ph->mutex->check))
			// return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));
		// usleep(10);
	// }
	// if (pthread_mutex_unlock(&ph->mutex->check))
		// return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));
	// if (pthread_mutex_lock(&ph->mutex->check))
		// return (ft_perror("[Error] pthread_mutex_lock check\n", -1));
	// ph->fork[ph->id] = UNUSABLE;
	// if (pthread_mutex_unlock(&ph->mutex->check))
	// ph->fork[(ph->id + 1) % ph->info->nr_philos] = UNUSABLE;
		// return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));
	// 여기 시간 측정
	// if (get_msec(&ph->time) == -1)
		// return (ft_perror("[Error] get_msec\n", -1));
	// printf("\t\t\t%ldms\t"GRN"%d wait mutex lock\n"EOC, ph->time - ph->info->time_start, ph->id + 1);

	// if (pthread_mutex_lock(&ph->mutex->philo[ph->id]))
		// return (ft_perror("[Error] pthread_mutex_lock philo\n", -1));
	//printf("\t\t[%d] fork[l]=%d fork[r]=%d \n", ph->id, ph->fork[ph->id], ph->fork[(ph->id + 1) % ph->info->nr_philos]);
	// 여기 시간 측정
	// if (get_msec(&ph->time) == -1)
		// return (ft_perror("[Error] get_msec\n", -1));
	// printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	// printf("l=%d r=%d\n", ph->fork[ph->id], ph->fork[(ph->id + 1) % ph->info->nr_philos]);
	return (0);
}

int	eating(t_philo *ph)
{
	if (get_msec(&ph->time) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	ph->time_last_dine = ph->time;
	printf("%ldms\t"YEL"%d is eating\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	if (thread_msleep(ph->info->time_eat, ph->time) == -1)
		return (ft_perror("[Error] thread_msleep\n", -1));
	ph->time_last_dine += (long int)ph->info->time_eat;
	printf("%ldms\t"YEL"%d is eating\n"EOC, ph->time - ph->info->time_start, ph->id + 1);
	// if (get_msec(&ph->time_last_dine) == -1)
	// 	return (ft_perror("[Error] get_msec\n", -1));
	return (0);
}

int	putdown(t_philo *ph)
{
	int	l;
	int	r;

	l = ph->id;
	r = RIGHT(ph->id, ph->info->nr_philos);
	if (ph->id & 1)
	{
		if (pthread_mutex_unlock(&ph->mutex->philo[l]))
			return (ft_perror("[Error] pthread_mutex_unlock philo\n", -1));
		if (pthread_mutex_unlock(&ph->mutex->philo[r]))
			return (ft_perror("[Error] pthread_mutex_unlock philo\n", -1));
	}
	else
	{
		if (pthread_mutex_unlock(&ph->mutex->philo[r]))
			return (ft_perror("[Error] pthread_mutex_unlock philo\n", -1));
		if (pthread_mutex_unlock(&ph->mutex->philo[l]))
			return (ft_perror("[Error] pthread_mutex_unlock philo\n", -1));
	}

	// if (pthread_mutex_lock(&ph->mutex->check))
		// return (ft_perror("[Error] pthread_mutex_lock check in putdown\n", -1));
	// ph->fork[l] = USABLE;
	// ph->fork[r] = USABLE;
	// printf("\t\t\t %d putdown forks\n", ph->id + 1);
	// if (ph->id == 0)
	// {
		// if (check(ph->left, ph) == -1)
			// return (ft_perror("[Error] check left_philo\n", -1));
		// if (check(ph->right, ph) == -1)
			// return (ft_perror("[Error] check right_philo\n", -1));
	// }
	// else
	// {
		// if (check(ph->right, ph) == -1)
			// return (ft_perror("[Error] check left_philo\n", -1));
		// if (check(ph->left, ph) == -1)
			// return (ft_perror("[Error] check right_philo\n", -1));
		// printf("filp=%d\n", ph->filp);
	// }
	// ph->filp = !ph->filp;

	// if (pthread_mutex_unlock(&ph->mutex->check))
		// return (ft_perror("[Error] pthread_mutex_unlock check\n", -1));

	++(ph->nr_dininig);
	if (ph->nr_dininig == ph->info->nr_must_eat)
		++(ph->info->nr_end_dine);
	if (ph->info->nr_end_dine == ph->info->nr_philos)
	{
		if (ph->nr_dininig == ph->info->nr_must_eat)
		{
			printf("[%d] eat %d dine --- num_must_eat=%d, num_end_dine=%d\n", ph->id + 1, ph->nr_dininig, ph->info->nr_must_eat, ph->info->nr_end_dine);
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
