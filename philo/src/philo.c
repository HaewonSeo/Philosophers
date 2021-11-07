/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:07:04 by haseo             #+#    #+#             */
/*   Updated: 2021/11/07 23:14:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
	info->num_philo = arg_to_int(argv[1]);
	info->time_die = arg_to_int(argv[2]);
	info->time_eat = arg_to_int(argv[3]);
	info->time_sleep = arg_to_int(argv[4]);
	if (argc == 6)
		info->num_must_eat = arg_to_int(argv[5]);
	if (info->num_philo <= 1 || info->time_die <= 0 || info->time_eat <= 0 || \
		info->time_sleep <= 0 || info->num_must_eat < 0)
		return (ft_perror("[Error] invaild argument\n", -1));
	return (0);
}

int	init_mutex(t_mutex *mutex, int n)
{
	int	i;

	mutex->philo = (pthread_mutex_t *)ft_calloc(n, sizeof(pthread_mutex_t));
	if (!mutex->philo)
		return (ft_perror("[Error] calloc mutex_philo\n", -1));
	if (pthread_mutex_init(&mutex->check, NULL))
		return (ft_perror("[Error] mutex_init check\n", -1));
	if (pthread_mutex_init(&mutex->simulation, NULL))
		return (ft_perror("[Error] mutex_init simulation\n", -1));
	if (pthread_mutex_lock(&mutex->simulation))
		return (ft_perror("[Error] pthread_mutex_lock simulation\n", -1));
	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&mutex->philo[i], NULL))
			return (ft_perror("[Error] mutex_init philo[i].mutex\n", -1));
		if (pthread_mutex_lock(&mutex->philo[i]))
			return (ft_perror("[Error] mutex_lock philo[i].mutex\n", -1));
	}
	return (0);
}

int	init_philo(t_philo *ph, t_info *info, t_mutex *mutex)
{
	int					i;
	t_fork				*fork;

	fork = (t_fork *)ft_calloc(info->num_philo, sizeof(t_fork));
	if (!fork)
		return (ft_perror("[Error] calloc fork\n", -1));
	i = -1;
	while (++i < info->num_philo)
	{
		ph[i].id = i;
		ph[i].left = LEFT(i, info->num_philo);
		ph[i].right = RIGHT(i, info->num_philo);
		ph[i].info = info;
		ph[i].mutex = mutex;
		ph[i].fork = fork;
	}
	return (0);
}

void free_all(t_philo *ph)
{
	int	i;

	pthread_mutex_destroy(&ph->mutex->check);
	pthread_mutex_destroy(&ph->mutex->simulation);
	i = -1;
	while (++i < ph->info->num_philo)
		pthread_mutex_destroy(&ph->mutex->philo[i]);
	free(ph->mutex->philo);
	free(ph->fork);
	free(ph);
}

int	main(int argc, char *argv[])
{
	t_info info;
	t_mutex mutex;
	t_philo *ph;

	if (argc != 5 && argc != 6)
		return (ft_perror("[Usage] ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 0));

	if (init_info(&info, argc, argv) == -1)
		return (ft_perror("[Error] init_info\n", 0));

	if (init_mutex(&mutex, info.num_philo) == -1)
		return (ft_perror("[Error] init_mutex\n", 0));

	ph = (t_philo *)ft_calloc(info.num_philo, sizeof(t_philo));
	if (!ph)
		return (ft_perror("[Error] calloc ph\n", 0));

	if (init_philo(ph, &info, &mutex) == -1)
		return (ft_perror("[Error] init_philo\n", 0));

	printf("Start simulation\n");
	if (threading(ph) == -1)
		return (ft_perror("[Error] threading\n", 0));;
	printf("End simulation\n");

	free_all(ph);

	return (0);
}
