/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:56:07 by hyun              #+#    #+#             */
/*   Updated: 2021/12/16 14:17:16 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preprocess_pipe_write(t_info *info)
{
	dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
	close(info->pipe_in[WRITE_END]);
}

int	preprocess_l1(t_info *info)
{
	int	fd;

	fd = open(info->l1_path, O_RDONLY);
	if (fd > 0)
	{
		printf("l1 success!\n");
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (0);
	}
	else
	{
		printf("minishell: no such file or directory: %s\n", info->l1_path);
		return (1);
	}
}

void	preprocess_l2(t_info *info)
{
	char	*input;

	pipe(info->l2_pipe);
	while (true)
	{
		input = get_eof_input();
		if (!ft_strncmp(input, info->l2_eof_word,
				ft_strlen(info->l2_eof_word) + 1))
			break ;
		write(info->l2_pipe[WRITE_END], input, ft_strlen(input) + 1);
	}
	close(info->l2_pipe[WRITE_END]);
	dup2(info->l2_pipe[READ_END], STDIN_FILENO);
	close(info->l2_pipe[READ_END]);
}

void	preprocess_r1(t_info *info)
{
	int	fd;

	fd = open(info->r1_path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	preprocess_r2(t_info *info)
{
	int	fd;

	fd = open(info->r2_path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
