/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:05:38 by jrobert           #+#    #+#             */
/*   Updated: 2021/12/07 17:51:12 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*dst;
	char	*tmp;
	int		size;

	if (!s1)
		size = ft_strlen(s2);
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)s1;
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	while (s1 && *s1)
		*dst++ = *s1++;
	if (tmp)
		free(tmp);
	while (*s2)
		*dst++ = *s2++;
	*dst = 0;
	return (dst - size);
}

static int	ft_save_line(int *endl, char buf[], int *i, char **line)
{
	int	start;

	start = *i;
	while (*i < BUFFER_SIZE && buf[*i] != '\n')
		++*i;
	if (buf[*i] == '\n')
		*endl = 1;
	buf[*i] = 0;
	*line = ft_strjoin_gnl(*line, &buf[start]);
	if (!*line)
		return (0);
	while ((*i)--)
		buf[*i] = 0;
	return (1);
}

static int	ft_drain_buf(int *endl, char buf[], char **line)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && !buf[i])
		i++;
	if (i < BUFFER_SIZE)
		return (ft_save_line(endl, buf, &i, line));
	return (1);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	int			endl;
	int			r;
	int			i;

	if (fd < 0 || fd >= OPEN_MAX || !line || !BUFFER_SIZE)
		return (-1);
	*line = 0;
	r = 1;
	endl = 0;
	if (!ft_drain_buf(&endl, buf, line))
		return (-1);
	while (!endl && r)
	{	
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (-1);
		i = 0;
		if (!ft_save_line(&endl, buf, &i, line))
			return (-1);
	}
	if (r > 0)
		return (1);
	else
		return (r);
}
