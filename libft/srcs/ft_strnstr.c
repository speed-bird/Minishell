/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:20:47 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 19:39:16 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (len-- && haystack[i])
	{
		if (haystack[i] == needle[j])
			j++;
		else
		{
			i -= j;
			len += j;
			j = 0;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i + 1 - j]);
		i++;
	}
	return (NULL);
}
