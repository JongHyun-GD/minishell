/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:02:32 by dason             #+#    #+#             */
/*   Updated: 2021/11/24 10:36:19 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_info(t_info *info, char **envp)
{
	info->envp = dup_envp(envp);
	info->is_pipe_in = false;
	info->is_pipe_out = false;
	return (0);
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
		flag = ft_export(list, info);
	else if (ft_strncmp(commandline, "unset", 5) == 0)
		flag = unset(list, info);
	else if (ft_strncmp(commandline, "pwd", 3) == 0)
		flag = pwd();
	else if (ft_strncmp(commandline, "cd", 2) == 0)
		flag = cd(list, info);
	else if (ft_strncmp(commandline, "echo", 4) == 0)
		flag = echo(list);
	else if (ft_strncmp(commandline, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (flag == -42)
		return (-1);
	return (0);
}

int	init_minishell(t_info *info, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (make_info(info, envp) == -1)
		return (-1);
	set_signal_parent();
	set_stty(info);
	return (0);
}

int	move_to_next_command_list(t_list **list)
{
	int	has_next;

	has_next = -1;
	*list = (*list)->next;
	while ((*list) && (*list)->l_type != LTYPE_COMMAND)
	{
		has_next = 0;
		*list = (*list)->next;
	}
	return (has_next);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;
	t_list	*list;

	if (init_minishell(&info, envp, argc, argv) == -1)
		return (-1);
	while (true)
	{
		str = get_user_input(&info);
		if (is_valid_input(str) == false)
			continue ;
		parser(&list, ft_strdup(str));
		while (true)
		{
			handle_redirect(list, &info);
			if (try_exec_builtin(str, list, &info) == -1)
				execute_non_builtin(make_argv_with_node(list), info.envp, &info);
			if (move_to_next_command_list(&list) == -1)
				break;
		}
		add_history(str);
		free(str);
		free_list_node(list);
	}
	return (0);
}
