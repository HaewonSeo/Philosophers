/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:52:52 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 22:57:01 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("%ldms\t"GRN"%d has taken a fork\n"EOC, ms, ph->id + 1);
	else if (state == EATING)
		printf("%ldms\t"YEL"%d is eating\n"EOC, ms, ph->id + 1);
	else if (state == SLEEPING)
		printf("%ldms\t"MAG"%d is sleeping\n"EOC, ms, ph->id + 1);
	else if (state == THINKING)
		printf("%ldms\t"CYN"%d is thinking\n"EOC, ms, ph->id + 1);
	else if (state == DIED)
		printf("%ldms\t"RED"%d died\n"EOC, ms, ph->id + 1);
	else if (state == COMPLETE)
		printf(BLU"All philosophers have eaten at least %d times\n"EOC, \
			ph->info->nr_must_eat);
	return (0);
}
