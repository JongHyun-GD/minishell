#include "../includes/executable.h"

int	excutable(t_list *list, char **argv, char **envp, t_info *info)
{
	pid_t	pid;
	pid_t	wait_pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		preprocess(list, info);
		if (execve(argv[0], argv, envp) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		wait_pid = wait(&pid);
		if (wait_pid < 0)
			return (-1);
		if (get_exit_result(pid) == 1)
			return (-1);
		postprocess(info);
	}
	return (0);
}