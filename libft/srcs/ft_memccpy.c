/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:11:39 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 13:35:57 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*str_dst;
	const char	*str_src;

	str_dst = dst;
	str_src = src;
	while (n--)
	{
		if ((unsigned char)*str_src == (unsigned char)c)
		{
			*str_dst++ = *str_src++;
			return (str_dst);
		}
		*str_dst++ = *str_src++;
	}
	return (NULL);
}
