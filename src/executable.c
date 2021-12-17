/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:19:46 by dason             #+#    #+#             */
/*   Updated: 2021/12/17 12:09:41 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executable.h"

void	excutable_child(t_list *list, char **argv, char **envp, t_info *info)
{
	if (ft_strchr(list->start_node->data, '/'))
	{
		if (preprocess(list, info) == 0)
			execve(argv[0], argv, envp);
		else
			exit(1);
	}
	exit(127);
}

int	executable(t_list *list, char **argv, char **envp, t_info *info)
{
	pid_t	pid;
	pid_t	wait_pid;

	pid = fork();
	set_signal_non_built_in();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		excutable_child(list, argv, envp, info);
	}
	else
	{
		wait_pid = wait(&pid);
		set_signal_parent();
		info->exit_status = get_exit_result(pid);
		if (wait_pid < 0 || info->exit_status == 127)
			return (-1);
		postprocess(info);
	}
	return (0);
}
