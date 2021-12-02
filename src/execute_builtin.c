/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/02 14:00:10 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *commandline)
{
	if (ft_strncmp(commandline, "env", ft_strlen(commandline)) == 0 || \
	ft_strncmp(commandline, "export", 6) == 0 || \
	ft_strncmp(commandline, "unset", 5) == 0 || \
	ft_strncmp(commandline, "pwd", 3) == 0 || \
	ft_strncmp(commandline, "cd", 2) == 0 || \
	ft_strncmp(commandline, "echo", 4) == 0 || \
	ft_strncmp(commandline, "exit", 4) == 0)
		return (true);
	return (false);
}

// TODO: Norminette - 25lines
int	try_exec_builtin(char *commandline, t_list *list, t_info *info)
{
	int	fd;

	if (is_builtin(commandline) == false)
		return (-1);
	if (info->has_pipe_in)
	{
		dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
		close(info->pipe_in[WRITE_END]);
		info->has_pipe_in = false;
	}
	if (info->has_redirect_r1)
	{
		printf("built in: path = %s,\n", info->r1_path);
		fd = open(info->r1_path, O_WRONLY | O_CREAT, 0755);
		printf("h1\n");
		dup2(fd, STDOUT_FILENO);
		printf("h2\n");
		close(fd);
		printf("h3\n");

	}
	if (list->prev && list->prev->l_type == LTYPE_PIPE)
	{
		dup2(info->pipe_out[READ_END], STDIN_FILENO);
		close(info->pipe_out[READ_END]);
	}
	if (ft_strncmp(commandline, "env", ft_strlen(commandline)) == 0)
		env(info);
	else if (ft_strncmp(commandline, "export", 6) == 0)
		ft_export(list, info);
	else if (ft_strncmp(commandline, "unset", 5) == 0)
		unset(list, info);
	else if (ft_strncmp(commandline, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(commandline, "cd", 2) == 0)
		cd(list, info);
	else if (ft_strncmp(commandline, "echo", 4) == 0)
		echo(list);
	else if (ft_strncmp(commandline, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (info->has_redirect_r1)
	{
		printf("r2\n");
		info->has_redirect_r1 = false;
	}

	return (0);
}
