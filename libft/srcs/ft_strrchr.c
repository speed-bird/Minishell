/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:20:52 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 17:49:36 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 1;
	while (*str)
	{
		i++;
		str++;
	}
	if ((char)c == '\0')
		return (str);
	while (i--)
		if (*str-- == (char)c)
			return (str + 1);
	return (NULL);
}
