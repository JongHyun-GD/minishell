/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/13 10:19:03 by hyun             ###   ########.fr       */
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

void	exec_builtin(char *commandline, t_list *list, t_info *info)
{
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
}

// TODO: Norminette - 25lines
int	try_exec_builtin(char *commandline, t_list *list, t_info *info)
{
	int		pid;
	int		status;

	if (is_builtin(commandline) == false)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		preprocess(info, list);
		exec_builtin(commandline, list, info);
		exit(0);
	}
	else
	{
		pid = wait(&status);
		if (pid < 0)
			return (-1);
		if (status >> 8 == 2)
			exit(0);
		postprocess(info);
	}
	return (0);
}
