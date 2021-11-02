/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:07:04 by haseo             #+#    #+#             */
/*   Updated: 2021/11/03 01:51:52 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*dine(void *arg)
{
	t_philo	*ph;
	int		ret;

	ph = (t_philo *)arg;

	while (1)
	{
		ret = 0;
		ret += pickup(ph);
		ret += eating(ph);
		ret += putdown(ph);
		ret += sleeping(ph);
		ret += thinking(ph);
		if (ret < 0)
			break;
	}

	return (NULL);
}

int	init_philo(t_philo *ph, t_info *info)
{
	int					i;
	pthread_mutex_t		check;
	pthread_mutex_t		*philo;
	t_state				*state;

	if (pthread_mutex_init(&check, NULL))
		return (ft_perror("[Error] mutex_init mutex_test\n", -1));
	philo = (pthread_mutex_t*)ft_calloc(info->num_philo, sizeof(pthread_mutex_t));
	if (!philo)
		return (ft_perror("[Error] calloc philo\n", -1));
	state = (t_state *)ft_calloc(info->num_philo, sizeof(t_state));
	if (!state)
		return (ft_perror("[Error] calloc state\n", -1));

	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_mutex_init(&philo[i], NULL))
			return (ft_perror("[Error] mutex_init philo[i].mutex\n", -1));
		if (pthread_mutex_lock(&philo[i]))
			return (ft_perror("[Error] mutex_lock philo[i].mutex\n", -1));
		state[i] = THINKING;
	}

	i = -1;
	while (++i < info->num_philo)
	{
		ph[i].id = i;
		ph[i].left = LEFT(i, info->num_philo);
		ph[i].right = RIGHT(i, info->num_philo);
		ph[i].info = info;
		ph[i].check = &check;
		ph[i].philo = philo;
		ph[i].state = state;
	}
	return (0);
}

int threading(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->info->num_philo)
	{
		if (pthread_create(&ph[i].tid, NULL, (void *)dine, (void *)&ph[i]))
			return (ft_perror("[Error] pthread_create\n", -1));
	}

	i = -1;
	while (++i < ph->info->num_philo)
	{
		if (pthread_join(ph[i].tid, NULL))
			return (ft_perror("[Error] pthread_detach\n", -1));
	}

	return (0);
}

int	init_info(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
	info->num_philo = arg_to_int(argv[1]);
	info->time_die = arg_to_int(argv[2]);
	info->time_eat = arg_to_int(argv[3]);
	info->time_sleep = arg_to_int(argv[4]);
	if (argc == 6)
		info->time_die = arg_to_int(argv[5]);
	if (info->num_philo <= 0 || info->time_die <= 0 || info->time_eat <= 0 || \
		info->time_sleep <= 0 || info->time_die < 0)
		return (ft_perror("[Error] invaild argument\n", -1));
	if (get_msec(&info->time_start) == -1)
		return (ft_perror("[Error] get_msec\n", -1));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info info;
	t_philo *ph;

	if (argc != 5 && argc != 6)
		return (ft_perror("[Usage] ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 0));

	if (init_info(&info, argc, argv) == -1)
		return (ft_perror("[Error] init_info\n", 0));

	ph = (t_philo *)ft_calloc(info.num_philo, sizeof(t_philo));
	if (!ph)
		return (ft_perror("[Error] calloc ph\n", 0));
	if (init_philo(ph, &info) == -1)
		return (ft_perror("[Error] init_philo\n", 0));
	if (threading(ph) == -1)
		return (ft_perror("[Error] threading\n", 0));;

	while (1)
		printf(".");

	return (0);
}
