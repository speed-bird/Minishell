/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:11:58 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/14 15:01:22 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*str_dest;
	const char		*str_src;

	if (!dest && !src)
		return (NULL);
	str_dest = dest;
	str_src = src;
	if (dest > src)
		while (n--)
			*(str_dest + n) = *(str_src + n);
	else
		while (n--)
			*str_dest++ = *str_src++;
	return (dest);
}
