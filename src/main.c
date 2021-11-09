#include "../includes/minishell.h"

int	make_info(t_info *info, char **envp)
{
	info->envp = dup_envp(envp);
	return (0);
}

// TODO: TEST funcs
t_list	*make_test_list1()
{
	t_list *list;
	t_node *node1, *node2, *node3;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));
	node3 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "export";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "aa==bb";
	node2->next = node3;
	node3->n_type = NTYPE_STRING;
	node3->data = "cc==dd";
	node3->next = NULL;

	list->start_node = node1;
	return (list);
}

// TODO: TEST funcs
t_list	*make_test_list2()
{
	t_list *list;
	t_node *node1, *node2, *node3;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));
	node3 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "export";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "aa==ss";
	node2->next = node3;
	node3->n_type = NTYPE_STRING;
	node3->data = "cc==zz";
	node3->next = NULL;

	list->start_node = node1;
	return (list);
}

// TODO: TEST funcs
t_list	*make_test_list_unset1()
{
	t_list *list;
	t_node *node1, *node2, *node3;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));
	node3 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "unset";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "aa";
	node2->next = node3;
	node3->n_type = NTYPE_STRING;
	node3->data = "cc";
	node3->next = NULL;

	list->start_node = node1;
	return (list);
}

// TODO: TEST funcs
t_list	*make_test_list_unset2()
{
	t_list *list;
	t_node *node1, *node2, *node3;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));
	node3 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "unset";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "aa";
	node2->next = node3;
	node3->n_type = NTYPE_STRING;
	node3->data = "kk=aa";
	node3->next = NULL;

	list->start_node = node1;
	return (list);
}

t_list	*make_test_list_cd1()
{
	t_list *list;
	t_node *node1;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "cd";
	node1->next = NULL;

	list->start_node = node1;
	return (list);
}

t_list	*make_test_list_cd2()
{
	t_list *list;
	t_node *node1, *node2;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "cd";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "etc";
	node2->next = NULL;

	list->start_node = node1;
	return (list);
}

t_list	*make_test_list_cd3()
{
	t_list *list;
	t_node *node1, *node2;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "cd";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "~/Documents";
	node2->next = NULL;

	list->start_node = node1;
	return (list);
}

t_list	*make_test_list_cd4()
{
	t_list *list;
	t_node *node1, *node2;

	list = (t_list *)malloc(sizeof(t_list));
	node1 = (t_node *)malloc(sizeof(t_node));
	node2 = (t_node *)malloc(sizeof(t_node));

	list->l_type = LTYPE_COMMAND;
	node1->n_type = NTYPE_COMMAND;
	node1->data = "cd";
	node1->next = node2;
	node2->n_type = NTYPE_STRING;
	node2->data = "..";
	node2->next = NULL;

	list->start_node = node1;
	return (list);
}

void	print_logo()
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

int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;
	t_list	*list;

	char	cwd_path[PATH_LENGTH];

	// TODO: Temp
	(void)argc;
	(void)argv;
	//

	if (make_info(&info, envp) == -1)
	{
		return (-1);
	}
	print_logo();
	while (1)
	{
		printf("%s", getcwd(cwd_path, PATH_LENGTH));
		str = readline(" > ");
		parser(&list, ft_strdup(str));
		print_list(list);
		if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		{
			env(&info);
		}
		else if (ft_strncmp(str, "export2", 7) == 0)
		{
			export(make_test_list2(), &info);
		}
		else if (ft_strncmp(str, "export", 6) == 0)
		{
			export(make_test_list1(), &info);
		}
		else if (ft_strncmp(str, "unset1", 6) == 0)
		{
			unset(make_test_list_unset1(), &info);
		}
		else if (ft_strncmp(str, "unset2", 6) == 0)
		{
			unset(make_test_list_unset2(), &info);
		}
		else if (ft_strncmp(str, "pwd", 3) == 0)
		{
			pwd();
		}
		else if (ft_strncmp(str, "cd1", 3) == 0)
		{
			cd(make_test_list_cd1(), &info);
		}
		else if (ft_strncmp(str, "cd2", 3) == 0)
		{
			cd(make_test_list_cd2(), &info);
		}
		else if (ft_strncmp(str, "cd3", 3) == 0)
		{
			cd(make_test_list_cd3(), &info);
		}
		else if (ft_strncmp(str, "cd4", 3) == 0)
		{
			cd(make_test_list_cd4(), &info);
		}
		else if (str)
		{
			printf("%s\n", str);
		}
		add_history(str);
		free(str);
		free_list_node(list);
	}
	return (0);
}
