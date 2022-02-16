/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:10:42 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/08 11:49:14 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		size;

	size = ft_numlen(n);
	dst = malloc((size + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[size--] = '\0';
	if (n < 0)
	{
		dst[0] = '-';
		dst[size--] = -1 * (n - ((n / 10) * 10)) + '0';
	}
	else
		dst[size--] = n - ((n / 10) * 10) + '0';
	n /= 10;
	if (n < 0)
		n = -n;
	while (n)
	{
		dst[size--] = n % 10 + '0';
		n /= 10;
	}
	return (dst);
}
