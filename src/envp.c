/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:09:59 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/02 13:38:48 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_lines(void)
{
	int		fd;
	int		count;
	char	read_char;

	fd = open(ENVP_PATH, O_RDONLY);
	count = 0;
	while (read(fd, &read_char, 1) > 0)
	{
		if (read_char == '\n')
			count++;
	}
	close(fd);
	return (count + 1);
}

char	**get_envp(void)
{
	int		fd;
	int		res;
	char	**lines;
	int		count;

	fd = open(ENVP_PATH, O_RDONLY);
	if (fd == -1)
	{
		printf("Error occured when open envp file");
		exit(-1);
	}
	lines = (char **)malloc(sizeof(char *) * count_lines());
	count = 0;
	while (1)
	{
		res = get_next_line(fd, &lines[count]);
		if (res <= 0)
			break ;
		count++;
	}
	close(fd);
	return (lines);
}
