/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:07:04 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 23:47:28 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_info(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
	info->nr_philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->nr_must_eat = ft_atoi(argv[5]);
	if (info->nr_philos <= 0 || info->time_die <= 0 || info->time_eat <= 0 || \
		info->time_sleep <= 0 || info->nr_must_eat < 0)
		return (ft_perror("[Error] invaild argument\n", -1));
	return (0);
}

static int	init_sem(t_sem *sem, int n)
{
	sem_unlink(SIMUL);
	sem->simulation = sem_open(SIMUL, O_CREAT, 0644, 0);
	if (sem->simulation == SEM_FAILED)
		return (ft_perror("[Error] sem_open()\n", -1));
	sem_unlink(COMPLETE);
	sem->complete = sem_open(COMPLETE, O_CREAT, 0644, 0);
	if (sem->complete == SEM_FAILED)
		return (ft_perror("[Error] sem_open()\n", -1));
	sem_unlink(FORKS);
	sem->forks = sem_open(FORKS, O_CREAT, 0644, n);
	if (sem->forks == SEM_FAILED)
		return (ft_perror("[Error] sem_open()\n", -1));
	return (0);
}

static void	init_philo(t_philo *ph, t_info *info, t_sem *sem)
{
	int	i;

	i = -1;
	while (++i < info->nr_philos)
	{
		ph[i].id = i;
		ph[i].info = info;
		ph[i].sem = sem;
	}
	return ;
}

static void	free_all(t_philo *ph)
{
	int	i;

	sem_close(ph->sem->simulation);
	sem_close(ph->sem->complete);
	sem_close(ph->sem->forks);
	if (kill(ph->info->pid_complete, SIGKILL) == -1)
		ft_perror("[Error] kill()\n", -1);
	if (waitpid(ph->info->pid_complete, NULL, WNOHANG) == -1)
		ft_perror("[Error] waitpid()\n", -1);
	i = -1;
	while (++i < ph->info->nr_philos)
	{
		if (ph[i].pid)
		{
			if (kill(ph[i].pid, SIGKILL) == -1)
				ft_perror("[Error] kill()\n", -1);
			if (waitpid(ph[i].pid, NULL, WNOHANG) == -1)
				ft_perror("[Error] waitpid()\n", -1);
		}
	}
	free(ph);
	return ;
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_sem	sem;
	t_philo	*ph;

	if (argc != 5 && argc != 6)
		return (ft_perror("[Usage] ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 0));
	if (init_info(&info, argc, argv) == -1)
		return (ft_perror("[Error] init_info()\n", 0));
	if (init_sem(&sem, info.nr_philos) == -1)
		return (ft_perror("[Error] init_sem()\n", 0));
	ph = (t_philo *)ft_calloc(info.nr_philos, sizeof(t_philo));
	if (!ph)
		return (ft_perror("[Error] ft_calloc() ph\n", 0));
	init_philo(ph, &info, &sem);
	if (simulation(ph) == -1)
		return (ft_perror("[Error] threading()\n", 0));
	free_all(ph);
	return (0);
}
