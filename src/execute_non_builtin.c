/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/13 20:03:18 by dason            ###   ########.fr       */
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

void	add_pipe_to_argv(char ***argv, t_info *info)
{
	char	str[8096];
	char	**new_argv;
	int		i;
	int		len;

	read(info->pipe_in[0], str, 8096);
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

static void	add_slash_to_str(char **s)
{
	char	*new_s;

	new_s = ft_strjoin(*s, "/");
	free(*s);
	*s = new_s;
}

static int	execute(char **argv, char **envp)
{
	char	**paths;
	int		i;
	size_t	len;
	char	*command;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
	}
	i = -1;
	while (paths[++i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
			add_slash_to_str(&paths[i]);
		command = make_command(argv, paths[i]);
		execve(command, argv, envp);
		free(command);
	}
	free_double_pointer(&paths);
	printf("minishell: %s: command not found\n", argv[0]);
	exit(127);
}

int	execute_non_builtin(t_list *list, char **argv, char **envp, t_info *info)
{
	int		pid;
	pid_t	wait_pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		preprocess(list, info);
		execute(argv, envp);
	}
	else
	{
		wait_pid = wait(&pid);
		info->exit_status = get_exit_result(pid);
		if (wait_pid < 0)
			return (-1);
		postprocess(info);
	}
	free_double_pointer(&argv);
	return (0);
}
