/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/07 10:09:56 by jongpark         ###   ########.fr       */
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
	int	fd;
	int	pid;
	int	status;

	fd = -1;
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
		if (info->has_redirect_r1)
		{
			fd = open(info->r1_path, O_WRONLY | O_CREAT, 0755);
			dup2(fd, STDOUT_FILENO);
		}
		if (info->has_redirect_r2)
		{
			fd = open(info->r1_path, O_WRONLY | O_CREAT | O_APPEND, 0755);
			dup2(fd, STDOUT_FILENO);
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
		if (info->has_redirect_r1)
		{
			if (fd != -1)
				close(fd);
			info->has_redirect_r1 = false;
		}
		if (info->has_redirect_r2)
		{
			if (fd != -1)
				close(fd);
			info->has_redirect_r2 = false;
		}
	}
	return (0);
}
