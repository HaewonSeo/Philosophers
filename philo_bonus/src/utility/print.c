/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:52:52 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 23:35:59 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_perror(const char *s, int errno)
{
	ft_putstr_fd(s, 2);
	return (errno);
}

int	print_state(t_philo *ph, t_state state)
{
	long int	ms;

	if (get_msec(&ph->time) == -1)
		return (ft_perror("[Error] get_msec()\n", -1));
	ms = ph->time - ph->info->time_start;
	if (state == TAKEN)
		printf(EOC"%ldms\t"GRN"%d has taken a fork\n", ms, ph->id + 1);
	else if (state == EATING)
		printf(EOC"%ldms\t"YEL"%d is eating\n", ms, ph->id + 1);
	else if (state == SLEEPING)
		printf(EOC"%ldms\t"MAG"%d is sleeping\n", ms, ph->id + 1);
	else if (state == THINKING)
		printf(EOC"%ldms\t"CYN"%d is thinking\n", ms, ph->id + 1);
	else if (state == DIED)
		printf(EOC"%ldms\t"RED"%d died\n", ms, ph->id + 1);
	return (0);
}
