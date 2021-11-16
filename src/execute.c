/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:02:23 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/16 11:02:25 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_command(char	**argv)
{
	int		command_length;
	char	*command;

	command_length = strlen(argv[0]) + 6;
	command = (char *)ft_calloc(command_length, 1);
	if (command == NULL)
		return (NULL);
	ft_strlcpy(command, "/bin/", command_length);
	ft_strlcat(command, argv[0], command_length);
	return (command);
}

int	execute_non_builtin(char **argv, char **envp)
{
	char	*command;
	int		flag;
	pid_t	wait_pid;

	command = make_command(argv);
	if (command == NULL)
		return (-1);
	flag = fork();
	if (flag < 0)
		return (-1);
	else if (flag == 0)
	{
		flag = execve(command, argv, envp);
		if (flag == -1)
			printf("minishell: %s: command not found\n", argv[0]);
		exit(0);
	}
	else
	{
		wait_pid = wait(&flag);
		if (wait_pid < 0)
			return (-1);
		free(command);
	}
	return (0);
}
