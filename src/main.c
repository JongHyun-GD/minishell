#include "../includes/minishell.h"

int	make_info(t_info *info, char **envp)
{
	info->envp = dup_envp(envp);
	return (0);
}

void	print_logo(void)
{
	int		fd;
	char	*line;

	fd = open(LOGO_PATH, O_RDONLY);
	line = (char *)ft_calloc(LOGO_LENGTH, 1);
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
	}
	close(fd);
	free(line);
}

char	**make_argv_with_node(t_list *list)
{
	int		size;
	t_node	*node;
	char	**argv;

	node = list->start_node;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	argv = (char **)ft_calloc(size + 1, sizeof(char *));
	size = 0;
	node = list->start_node;
	while (node)
	{
		argv[size++] = ft_strdup(node->data);
		node = node->next;
	}
	return (argv);
}

int	try_exec_builtin(char *commandline, t_list *list, t_info *info)
{
	int	flag;

	flag = -42;
	if (ft_strncmp(commandline, "env", ft_strlen(commandline)) == 0)
		flag = env(info);
	else if (ft_strncmp(commandline, "export", 6) == 0)
		flag = export(list, info);
	else if (ft_strncmp(commandline, "unset", 5) == 0)
		flag = unset(list, info);
	else if (ft_strncmp(commandline, "pwd", 3) == 0)
		flag = pwd();
	else if (ft_strncmp(commandline, "cd", 2) == 0)
		flag = cd(list, info);
	else if (ft_strncmp(commandline, "echo", 4) == 0)
		flag = echo(list);
	if (flag == -42)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;
	t_list	*list;
	char	cwd_path[PATH_LENGTH];

	(void)argc;
	(void)argv;
	if (make_info(&info, envp) == -1)
		return (-1);
	print_logo();
	while (1)
	{
		printf("%s", getcwd(cwd_path, PATH_LENGTH));
		str = readline(" > ");
		parser(info, &list, ft_strdup(str));
		if (try_exec_builtin(str, list, &info) == -1)
			execute_non_builtin(make_argv_with_node(list), info.envp);
		add_history(str);
		free(str);
		free_list_node(list);
	}
	return (0);
}
