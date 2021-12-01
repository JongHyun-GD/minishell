/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/01 14:06:54 by jongpark         ###   ########.fr       */
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

// TODO: temp_command
// TODO: norminette
int	execute_non_builtin(t_list *list, char **argv, char **envp, t_info *info)
{
	int		pid;
	pid_t	wait_pid;
	char	*tmp_command;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (info->has_pipe_in)
		{
			printf("is_pipe_in!\n");
			dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
			close(info->pipe_in[WRITE_END]);
		}
		if (list->prev && list->prev->l_type == LTYPE_PIPE)
		{
			dup2(info->pipe_out[READ_END], STDIN_FILENO);
			close(info->pipe_out[READ_END]);
		}
		tmp_command = make_command(argv, "/bin/");
		pid = execve(tmp_command, argv, envp);
		if (pid < 0)
		{
			tmp_command = make_command(argv, "/usr/bin/");
			pid = execve(tmp_command, argv, envp);
		}
		if (pid < 0)
			printf("minishell: %s: command not found\n", argv[0]);
		exit(0);
	}
	else
	{
		wait_pid = wait(&pid);
		if (wait_pid < 0)
			return (-1);
		if (info->has_pipe_in)
		{
			close(info->pipe_in[WRITE_END]);
			info->has_pipe_in = false;
		}
	}
	free_double_pointer(&argv);
	return (0);
}
