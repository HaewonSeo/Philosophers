/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:07:04 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 16:22:41 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	init_mutex(t_mutex *mutex, int n)
{
	int	i;

	mutex->fork = (pthread_mutex_t *)ft_calloc(n, sizeof(pthread_mutex_t));
	if (!mutex->fork)
		return (ft_perror("[Error] ft_calloc() mutex_fork\n", -1));
	if (pthread_mutex_init(&mutex->simulation, NULL))
		return (ft_perror("[Error] mutex_init(simulation)\n", -1));
	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&mutex->fork[i], NULL))
			return (ft_perror("[Error] mutex_init(fork[])\n", -1));
	}
	return (0);
}

static int	init_philo(t_philo *ph, t_info *info, t_mutex *mutex)
{
	int	i;

	i = -1;
	while (++i < info->nr_philos)
	{
		ph[i].id = i;
		ph[i].l = i;
		ph[i].r = (i + 1) % info->nr_philos;
		ph[i].info = info;
		ph[i].mutex = mutex;
	}
	return (0);
}

static void	free_all(t_philo *ph)
{
	int	i;

	pthread_mutex_destroy(&ph->mutex->simulation);
	i = -1;
	while (++i < ph->info->nr_philos)
		pthread_mutex_destroy(&ph->mutex->fork[i]);
	free(ph->mutex->fork);
	ph->mutex->fork = NULL;
	free(ph);
	ph = NULL;
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_mutex	mutex;
	t_philo	*ph;

	if (argc != 5 && argc != 6)
		return (ft_perror("[Usage] ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 0));
	if (init_info(&info, argc, argv) == -1)
		return (ft_perror("[Error] init_info()\n", 0));
	if (init_mutex(&mutex, info.nr_philos) == -1)
		return (ft_perror("[Error] init_mutex()\n", 0));
	ph = (t_philo *)ft_calloc(info.nr_philos, sizeof(t_philo));
	if (!ph)
		return (ft_perror("[Error] ft_calloc() ph\n", 0));
	if (init_philo(ph, &info, &mutex) == -1)
		return (ft_perror("[Error] init_philo()\n", 0));
	if (threading(ph) == -1)
		return (ft_perror("[Error] threading()\n", 0));
	free_all(ph);
	return (0);
}
