/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argtoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:19:47 by haseo             #+#    #+#             */
/*   Updated: 2021/11/07 23:14:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
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
