/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/01 15:00:20 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *commandline)
{
	if (ft_strncmp(commandline, "env", ft_strlen(commandline)) == 0 ||
	ft_strncmp(commandline, "export", 6) == 0 ||
	ft_strncmp(commandline, "unset", 5) == 0 ||
	ft_strncmp(commandline, "pwd", 3) == 0 ||
	ft_strncmp(commandline, "cd", 2) == 0 ||
	ft_strncmp(commandline, "echo", 4) == 0 ||
	ft_strncmp(commandline, "exit", 4) == 0)
		return (true);
	return (false);
}

int	try_exec_builtin(char *commandline, t_list *list, t_info *info)
{
	if (is_builtin(commandline) == false)
		return (-1);
	if (info->has_pipe_in)
	{
		dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
		close(info->pipe_in[WRITE_END]);
		info->has_pipe_in = false;
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
	return (0);
}
