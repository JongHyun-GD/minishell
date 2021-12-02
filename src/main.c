/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:02:32 by dason             #+#    #+#             */
/*   Updated: 2021/12/02 16:42:04 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_info(t_info *info, char **envp)
{
	info->envp = dup_envp(envp);
	info->has_pipe_in = false;
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
	argv[size] = NULL;
	return (argv);
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
	int		has_next;

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
	t_list	*origin_list;

	if (init_minishell(&info, envp, argc, argv) == -1)
		return (-1);
	while (true)
	{
		str = get_user_input(&info);
		if (is_valid_input(str) == false)
			continue ;
		parser(&list, ft_strdup(str));
		origin_list = list;
		while (list)
		{
			handle_redirect(list, &info);
			if (try_exec_builtin(str, list, &info) == -1)
				execute_non_builtin(list, make_argv_with_node(list), info.envp, &info);
			swap_pipe(&info);
			if (move_to_next_command_list(&list) == -1)
				break;
		}
		add_history(str);
		free(str);
		free_list_node(&origin_list);
	}
	return (0);
}
