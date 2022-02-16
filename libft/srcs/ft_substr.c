/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:21:07 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 19:41:38 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	strlen;
	size_t	dstlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		dstlen = 0;
	else
		dstlen = strlen - start;
	if (len < dstlen)
		dstlen = len;
	dst = malloc((dstlen + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[dstlen] = 0;
	while (dstlen--)
		dst[dstlen] = s[start + dstlen];
	return (dst);
}
