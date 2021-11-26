/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/24 15:04:04 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_command(char	**argv, char *location)
{
	int		command_length;
	char	*command;

	command_length = strlen(argv[0]) + ft_strlen(location) + 1;
	command = (char *)ft_calloc(command_length, 1);
	if (command == NULL)
		return (NULL);
	ft_strlcpy(command, location, command_length);
	ft_strlcat(command, argv[0], command_length);
	return (command);
}

void add_pipe_to_argv(char ***argv, t_info *info)
{
	char	str[8096];
	char	**new_argv;
	int		i;
	int		len;

	read(info->pipe[0], str, 8096);
	len = 0;
	while ((*argv)[len])
		len++;
	new_argv = (char **)ft_calloc(sizeof(char *) * (len + 2), 1);
	i = 0;
	while (i < len)
	{
		new_argv[i] = (*argv)[i];
		i++;
	}
	new_argv[i] = str;
	free(*argv);
	*argv = new_argv;
}

int	execute_non_builtin(char **argv, char **envp, t_info *info)
{
	int		flag;
	pid_t	wait_pid;

	flag = fork();
	if (flag < 0)
		return (-1);
	if (flag == 0)
	{
		if (info->is_pipe_in)
			dup2(info->pipe[1], STDOUT_FILENO);
		if (info->is_pipe_out)
		{
			dup2(info->pipe[0], STDIN_FILENO);
			close(info->pipe[0]);
		}
		flag = execve(make_command(argv, "/bin/"), argv, envp);
		if (flag < 0)
			flag = execve(make_command(argv, "/usr/bin/"), argv, envp);
		if (flag < 0)
			printf("minishell: %s: command not found\n", argv[0]);
		exit(0);
	}
	else
	{
		wait_pid = wait(&flag);
		printf("\nchild proc dead!\n");
		if (wait_pid < 0)
			return (-1);
		if (info->is_pipe_out)
		{
			info->is_pipe_out = false;
		}
		if (info->is_pipe_in)
		{
			info->is_pipe_in = false;
			info->is_pipe_out = true;
		}
	}
	free_double_pointer(&argv);
	return (0);
}
