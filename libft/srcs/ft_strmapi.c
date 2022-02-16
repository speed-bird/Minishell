/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:20:38 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/10 20:42:15 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*dst;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	dst = malloc((size + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst[size] = '\0';
	while (size--)
		dst[size] = f(size, s[size]);
	return (dst);
}
