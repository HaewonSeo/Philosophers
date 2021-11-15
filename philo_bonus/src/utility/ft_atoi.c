/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:19:47 by haseo             #+#    #+#             */
/*   Updated: 2021/11/15 18:40:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	valid_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	while (s[i++])
		len++;
	if (len > 10)
		return (-1);
	return (len);
}

int	ft_atoi(char *s)
{
	int			i;
	int			sign;
	long long	num;

	if (valid_len(s) == -1)
		return (-1);
	i = 0;
	sign = 1;
	num = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		num = num * 10 + (s[i++] - '0');
	}
	num *= sign;
	if (num > MAXINT || num < MININT)
		return (-1);
	return ((int)num);
}
