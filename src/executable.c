/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:19:46 by dason             #+#    #+#             */
/*   Updated: 2021/12/15 17:23:32 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executable.h"

int	executable(t_list *list, char **argv, char **envp, t_info *info)
{
	pid_t	pid;
	pid_t	wait_pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (ft_strchr(list->start_node->data, '/'))
		{
			preprocess(list, info);
			execve(argv[0], argv, envp);
		}
		exit(127);
	}
	else
	{
		wait_pid = wait(&pid);
		info->exit_status = get_exit_result(pid);
		if (wait_pid < 0 || info->exit_status == 127)
			return (-1);
		postprocess(info);
	}
	return (0);
}
