/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/07 13:10:24 by jongpark         ###   ########.fr       */
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
	exit(0);
}

// TODO: norminette - 25 lines
int	execute_non_builtin(t_list *list, char **argv, char **envp, t_info *info)
{
	int		pid;
	pid_t	wait_pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (info->has_pipe_in)
		{
			dup2(info->pipe_in[WRITE_END], STDOUT_FILENO);
			close(info->pipe_in[WRITE_END]);
		}
		if (info->has_redirect_r1)
		{
			fd = open(info->r1_path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (info->has_redirect_r2)
		{
			fd = open(info->r2_path, O_WRONLY | O_CREAT | O_APPEND, 0755);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (info->has_redirect_l1)
		{
			write(STDIN_FILENO, info->l1_data, info->l1_data_len);
		}
		if (list->prev && list->prev->l_type == LTYPE_PIPE)
		{
			dup2(info->pipe_out[READ_END], STDIN_FILENO);
			close(info->pipe_out[READ_END]);
		}
		execute(argv, envp);
	}
	else
	{
		wait_pid = wait(&pid);
		printf("child proc is dead!\n");
		if (wait_pid < 0)
			return (-1);
		if (info->has_pipe_in)
		{
			close(info->pipe_in[WRITE_END]);
			info->has_pipe_in = false;
		}
		if (info->has_redirect_r1)
		{
			info->has_redirect_r1 = false;
		}
		if (info->has_redirect_r2)
		{
			info->has_redirect_r2 = false;
		}
		if (info->has_redirect_l1)
		{
			info->has_redirect_l1 = false;
		}
	}
	free_double_pointer(&argv);
	return (0);
}
