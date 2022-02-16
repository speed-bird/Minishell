/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:08:51 by jrobert           #+#    #+#             */
/*   Updated: 2022/01/14 20:06:28 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long unsigned	val;
	long unsigned	limit;
	int				sign;

	val = 0;
	limit = 922337203685477580;
	sign = 1;
	while (*str == 32 || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && val < limit)
		val = val * 10 + *str++ - 48;
	if (val == limit && ((sign == 1 && *str <= '7')
			|| (sign == -1 && *str <= '8')))
		val = val * 10 + *str - 48;
	else if (val >= limit && sign == 1)
		return (-1);
	else if (val >= limit && sign == -1)
		return (0);
	return (sign * val);
}
