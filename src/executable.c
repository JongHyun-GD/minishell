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
		printf("exit status: %d\n", info->exit_status);
		if (wait_pid < 0)
			return (-1);
		if (get_exit_result(pid) == 127)
			return (-1);
		postprocess(info);
	}
	return (0);
}