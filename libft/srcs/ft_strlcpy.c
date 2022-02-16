/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:13:33 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 16:40:17 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;

	src_length = 0;
	while (*src)
	{
		if (dstsize > 0 && src_length < dstsize - 1)
			*dst++ = *src++;
		else
			src++;
		src_length++;
	}
	if (dstsize > 0)
		*dst = 0;
	return (src_length);
}
