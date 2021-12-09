/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/08 20:25:48 by dason            ###   ########.fr       */
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
	int		fd_r;
	int		fd_l;
	char	*input;

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
		if (info->has_redirect_l1)
		{
			fd_l = open(info->l1_path, O_RDONLY);
			if (fd_l > 0)
			{
				dup2(fd_l, STDIN_FILENO);
				close(fd_l);
			}
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
			close(fd_r);
		}
		if (info->has_redirect_r2)
		{
			fd_r = open(info->r2_path, O_WRONLY | O_CREAT | O_APPEND, 0755);
			dup2(fd_r, STDOUT_FILENO);
			close(fd_r);
		}
		if (list->prev && list->prev->l_type == LTYPE_PIPE)
		{
			dup2(info->pipe_out[READ_END], STDIN_FILENO);
			close(info->pipe_out[READ_END]);
		}
		if (list->prev && list->prev->l_type == LTYPE_REDIRECT_L2)
		{
			dup2(info->pipe_out[READ_END], STDIN_FILENO);
		}
		execute(argv, envp);
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
		if (info->has_redirect_l1)
		{
			info->has_redirect_l1 = false;
		}
		if (info->has_redirect_l2)
		{
			close(info->l2_pipe[WRITE_END]);
			info->has_redirect_l2 = false;
		}
		if (info->has_redirect_r1)
		{
			info->has_redirect_r1 = false;
		}
		if (info->has_redirect_r2)
		{
			info->has_redirect_r2 = false;
		}
	}
	free_double_pointer(&argv);
	return (0);
}
