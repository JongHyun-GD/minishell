/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:40:02 by jongpark          #+#    #+#             */
/*   Updated: 2020/12/30 19:22:28 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			gnl_clean_up(char **line, char *buf, char **backup)
{
	free(*backup);
	*backup = NULL;
	*line = buf;
	return (0);
}

void		*gnl_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (!(ptr = (void *)malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

size_t		gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (src[i] && i < dstsize - 1 && dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

char		*gnl_buf_has_break(char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (NULL);
	return (&s[i]);
}

int			gnl_check_invalid(char **line, int fd, char **backup)
{
	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!(*backup) && !((*backup) = (char *)gnl_calloc(BUFFER_SIZE + 1, 1)))
		return (-1);
	return (0);
}
