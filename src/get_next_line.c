/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:59:48 by jongpark          #+#    #+#             */
/*   Updated: 2020/12/30 17:54:18 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		gnl_backup_to_buf(char *backup, char *buf, size_t *readbyte)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*readbyte = 0;
	while (backup[i])
	{
		buf[i] = backup[i];
		*readbyte = (*readbyte) + 1;
		i++;
	}
	if (backup[i] == 0)
		return ;
	i++;
	gnl_strlcpy(&backup[0], &backup[i], i);
	return ;
}

static char		*gnl_double_buf(char **buf, size_t *bufsize)
{
	char	*ret;
	size_t	i;

	i = -1;
	*bufsize = (*bufsize) * 2;
	if (!(ret = (char *)gnl_calloc((*bufsize) + 1, 1)))
		return (0);
	while ((*buf)[++i])
		ret[i] = (*buf)[i];
	free(*buf);
	*buf = ret;
	return (&ret[i]);
}

static int		gnl_read_buf(char *ptr, size_t *readbyte, int fd)
{
	int		flag;

	flag = read(fd, ptr, BUFFER_SIZE);
	if (flag == -1)
		return (-1);
	ptr = ptr + flag;
	(*readbyte) += flag;
	if (flag == 0)
		return ((*readbyte) = 0);
	return (flag);
}

static void		gnl_buf_to_backup(char *buf, char *backup)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == 0)
		return ;
	else
	{
		buf[i] = 0;
		i++;
		while (buf[i])
		{
			backup[j] = buf[i];
			buf[i] = 0;
			i++;
			j++;
		}
		backup[j] = 0;
	}
	return ;
}

int				get_next_line(int fd, char **line)
{
	static char	*backup[OPEN_MAX];
	char		*buf;
	char		*ptr;
	size_t		bufsize;
	size_t		readbyte;

	bufsize = BUFFER_SIZE;
	if (gnl_check_invalid(line, fd, &backup[fd]))
		return (-1);
	if (!(buf = (char *)gnl_calloc(bufsize + 1, 1)))
		return (-1);
	gnl_backup_to_buf(backup[fd], buf, &readbyte);
	ptr = buf;
	while ((ptr = gnl_buf_has_break(ptr)) != NULL)
	{
		if (bufsize < readbyte + BUFFER_SIZE)
			ptr = gnl_double_buf(&buf, &bufsize);
		if (gnl_read_buf(ptr, &readbyte, fd) == -1)
			return (-1);
		if (readbyte == 0)
			return (gnl_clean_up(line, buf, &backup[fd]));
	}
	gnl_buf_to_backup(buf, backup[fd]);
	*line = buf;
	return (1);
}
