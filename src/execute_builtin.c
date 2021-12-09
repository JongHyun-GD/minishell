/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/08 20:26:16 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *commandline)
{
	if (ft_strncmp(commandline, "env", ft_strlen(commandline)) == 0 || \
	ft_strncmp(commandline, "export", 7) == 0 || \
	ft_strncmp(commandline, "unset", 6) == 0 || \
	ft_strncmp(commandline, "pwd", 4) == 0 || \
	ft_strncmp(commandline, "cd", 3) == 0 || \
	ft_strncmp(commandline, "echo", 5) == 0 || \
	ft_strncmp(commandline, "exit", 5) == 0)
		return (true);
	return (false);
}

// TODO: Norminette - 25lines
int	try_exec_builtin(char *commandline, t_list *list, t_info *info)
{
	int		fd_r;
	int		fd_l;
	int		pid;
	int		status;
	char	*input;

	fd_r = -1;
	fd_l = -1;
	if (is_builtin(commandline) == false)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (info->has_pipe_in)
		{
			dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
			close(info->pipe_in[WRITE_END]);
			info->has_pipe_in = false;
		}
		if (info->has_redirect_l1)
		{
			fd_l = open(info->l1_path, O_RDONLY);
			if (fd_l > 0)
				dup2(fd_l, STDIN_FILENO);
			else
				printf("minishell: no such file or directory: %s", info->l1_path);
		}
		if (info->has_redirect_l2)
		{
			pipe(info->l2_pipe);
			while (true)
			{
				input = get_eof_input();
				if (!ft_strncmp(input, info->l2_eof_word, ft_strlen(info->l2_eof_word) + 1))
					break;
				write(info->l2_pipe[WRITE_END], input, ft_strlen(input) + 1);
			}
			close(info->l2_pipe[WRITE_END]);
			dup2(info->l2_pipe[READ_END], STDIN_FILENO);
			close(info->l2_pipe[READ_END]);
		}
		if (info->has_redirect_r1)
		{
			fd_r = open(info->r1_path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
			dup2(fd_r, STDOUT_FILENO);
		}
		if (info->has_redirect_r2)
		{
			fd_r = open(info->r1_path, O_WRONLY | O_CREAT | O_APPEND, 0755);
			dup2(fd_r, STDOUT_FILENO);
		}
		if (list->prev && list->prev->l_type == LTYPE_PIPE)
		{
			dup2(info->pipe_out[READ_END], STDIN_FILENO);
			close(info->pipe_out[READ_END]);
		}
		if (ft_strncmp(commandline, "env", 4) == 0)
			env(info);
		else if (ft_strncmp(commandline, "export", 7) == 0)
			ft_export(list, info);
		else if (ft_strncmp(commandline, "unset", 6) == 0)
			unset(list, info);
		else if (ft_strncmp(commandline, "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(commandline, "cd", 3) == 0)
			cd(list, info);
		else if (ft_strncmp(commandline, "echo", 5) == 0)
			echo(list);
		else if (ft_strncmp(commandline, "exit", 5) == 0)
		{
			printf("exit\n");
			exit(2);
		}
		exit(0);
	}
	else
	{
		pid = wait(&status);
		if (pid < 0)
			return (-1);
		if (status >> 8 == 2)
			exit(0);
		if (info->has_redirect_l1)
		{
			if (fd_l != -1)
				close(fd_l);
			info->has_redirect_l1 = false;
		}
		if (info->has_redirect_l2)
		{
			info->has_redirect_l2 = false;
		}
		if (info->has_redirect_r1)
		{
			if (fd_r != -1)
				close(fd_r);
			info->has_redirect_r1 = false;
		}
		if (info->has_redirect_r2)
		{
			if (fd_r != -1)
				close(fd_r);
			info->has_redirect_r2 = false;
		}
	}
	return (0);
}
