/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:12:40 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/12 19:49:47 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;

	dst = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	dst[i] = 0;
	return (dst);
}
