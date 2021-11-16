/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:59:56 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/16 11:02:02 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(void)
{
	char	cwd_path[PATH_LENGTH];

	printf("%s", getcwd(cwd_path, PATH_LENGTH));
}

int	get_exit_result(int stat)
{
	return (stat >> 8);
}

void	readline_child(int *ipc_pipe)
{
	char	*buf;

	set_signal_child();
	print_prompt();
	buf = readline(" > ");
	if (buf == NULL)
		exit(STAT_CTRL_D);
	write(ipc_pipe[1], buf, ft_strlen(buf) + 1);
	exit(0);
}

char	*wait_child(int *ipc_pipe, t_info *info)
{
	char	*buf;
	int		stat;

	wait(&stat);
	if (get_exit_result(stat) == STAT_CTRL_D)
	{
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, &info->orig_term);
		printf("exit\n");
		exit(0);
		return (NULL);
	}
	if (get_exit_result(stat) == STAT_CTRL_C)
		return (NULL);
	buf = (char *)malloc(INPUT_BUFFER_SIZE);
	read(ipc_pipe[0], buf, BUFFER_SIZE);
	return (buf);
}

char	*get_user_input(t_info *info)
{
	pid_t	pid;
	int		ipc_pipe[2];

	pipe(ipc_pipe);
	pid = fork();
	if (pid == 0)
		readline_child(ipc_pipe);
	else if (pid > 0)
		return (wait_child(ipc_pipe, info));
	else
	{
		printf("minishell: fork error\n");
		return (NULL);
	}
	return (NULL);
}
