/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:21:00 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/10 15:54:05 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*dst;
	int		length;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	length = 0;
	while (*s1)
	{
		while (*s1 && ft_is_in_set(*s1++, set) && !length)
			start++;
		if (!ft_is_in_set(*(s1 - 1), set))
			length = s1 - start;
	}
	dst = malloc((length + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[length] = '\0';
	while (length--)
		dst[length] = *(start + length);
	return (dst);
}
