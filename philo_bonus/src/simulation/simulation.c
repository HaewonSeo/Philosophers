/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:06:25 by haseo             #+#    #+#             */
/*   Updated: 2021/11/16 00:00:32 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	monitor_completion(t_info *info, t_sem *sem)
{
	int	sem_value;

	sem_value = 0;
	while (sem_value < info->nr_philos)
	{
		if (sem_wait(sem->complete) == -1)
			ft_perror("[Error] sem_wait(complete)\n", -1);
		++sem_value;
	}
	printf(BLU"All philosophers have eaten at least %d times\n"EOC, \
			info->nr_must_eat);
	if (sem_post(sem->simulation))
		ft_perror("[Error] sem_post(simulation)\n", -1);
	return ;
}

static void	init_monitor_completion(t_info *info, t_sem *sem)
{
	info->pid_complete = fork();
	if (info->pid_complete == -1)
		ft_perror("[Error] fork()\n", -1);
	else if (info->pid_complete == 0)
	{
		monitor_completion(info, sem);
		exit(0);
	}
	return ;
}

static void	*monitor_death(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (get_msec(&ph->time) == -1)
			ft_perror("[Error] get_msec()\n", -1);
		if (ph->time - ph->time_last_dine > (long int)ph->info->time_die)
			break ;
		if (thread_msleep(20, ph->time) == -1)
			ft_perror("[Error] thread_msleep()\n", -1);
	}
	if (print_state(ph, DIED))
		ft_perror("[Error] print_state()\n", -1);
	if (sem_post(ph->sem->simulation))
		ft_perror("[Error] sem_post(simulation)\n", -1);
	return (NULL);
}

static void	dine(t_philo *ph)
{
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
	if (sem_post(ph->sem->simulation) == -1)
		ft_perror("[Error] sem_post(simulation)\n", -1);
	return ;
}

int	simulation(t_philo *ph)
{
	int	i;

	init_monitor_completion(ph->info, ph->sem);
	if (get_msec(&ph->info->time_start) == -1)
		return (ft_perror("[Error] get_msec()\n", -1));
	i = -1;
	while (++i < ph->info->nr_philos)
	{
		ph[i].time_last_dine = ph->info->time_start;
		ph[i].pid = fork();
		if (ph[i].pid == -1)
			return (ft_perror("[Error] fork()\n", -1));
		else if (ph[i].pid == 0)
		{
			if (pthread_create(&ph[i].tid, NULL, monitor_death, (void *)&ph[i]))
				return (ft_perror("[Error] pthread_create(monitor)\n", -1));
			if (pthread_detach(ph[i].tid))
				return (ft_perror("[Error] pthread_detach(monitor)\n", -1));
			dine(&ph[i]);
			exit(0);
		}
	}
	if (sem_wait(ph->sem->simulation) == -1)
		return (ft_perror("[Error] sem_wait()\n", -1));
	return (0);
}
