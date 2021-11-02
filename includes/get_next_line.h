/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:51:57 by jongpark          #+#    #+#             */
/*   Updated: 2020/12/30 19:21:33 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int		get_next_line(int fd, char **line);
int		gnl_clean_up(char **line, char *buf, char **backup);
void	*gnl_calloc(size_t count, size_t size);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_buf_has_break(char *s);
int		gnl_check_invalid(char **line, int fd, char **backup);

#endif
