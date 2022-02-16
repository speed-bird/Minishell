/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:12:26 by jrobert           #+#    #+#             */
/*   Updated: 2021/04/14 15:28:32 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
		while (*s && *s == c)
			s++;
	}
	return (words);
}

static void	*ft_free_mallocs(char **dst, int i)
{
	while (i)
		free(dst[--i]);
	free(dst);
	return (NULL);
}

static char	*ft_strdup_split(const char *s1, char c)
{
	char	*dst;
	int		size;
	int		i;

	size = 0;
	while (s1[size] && s1[size] != c)
		size++;
	dst = malloc((size + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (*s1 && *s1 != c)
		dst[i++] = *s1++;
	dst[i] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;
	int		t;

	if (!s)
		return (NULL);
	dst = malloc((ft_count_words(s, c) + 1) * sizeof(s));
	if (dst == NULL)
		return (NULL);
	i = -1;
	t = 0;
	while (s && s[++i])
	{
		if (s[i] != c)
		{
			dst[t] = ft_strdup_split(&s[i], c);
			if (dst[t++] == NULL)
				return (ft_free_mallocs(dst, t));
			while (s[i] != c && s[i + 1])
				i++;
		}
	}
	dst[t] = NULL;
	return (dst);
}
