/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:19:47 by haseo             #+#    #+#             */
/*   Updated: 2021/11/05 21:29:43 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*mem;

	mem = malloc(num * size);
	if (!mem)
		return (NULL);
	memset(mem, 0, (num * size));
	return (mem);
}

static int	valid_arg_len(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	while (arg[i++])
		len++;
	if (len > 10)
		return (-1);
	return (len);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	arg_to_int(char *arg)
{
	int			i;
	int			sign;
	long long	num;

	if (valid_arg_len(arg) == -1)
		return (-1);
	i = 0;
	sign = 1;
	num = 0;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		num = num * 10 + (arg[i++] - '0');
	}
	num *= sign;
	if (num > MAXINT || num < MININT)
		return (-1);
	return ((int)num);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(const char *s, int fd)
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

int	get_msec(long int *msec)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (ft_perror("[Error] gettimeofday\n", -1));
	*msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	//printf("%ld %ld\n", tv.tv_sec, tv.tv_usec);
	return (0);
}

int	thread_msleep(long int msec, long int time_start)
{
	long int time;

	while (1)
	{
		if (get_msec(&time) == -1)
			return (ft_perror("[Error] get_msec\n", -1));
		if (time - time_start >= msec)
			return (0);
		if (usleep(10) == -1)
			return (ft_perror("[Error] usleep\n", -1));
	}
}
