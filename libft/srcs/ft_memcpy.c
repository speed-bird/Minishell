/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:11:53 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 13:45:22 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*str_dest;
	const char	*str_src;

	str_dest = dest;
	str_src = src;
	if (!(!dest && !src))
		while (n--)
			*str_dest++ = *str_src++;
	return (dest);
}
