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
	node2->n_type = NTYPE_DATA;
	node2->data = "aa==bb";
	node2->next = node3;
	node3->n_type = NTYPE_DATA;
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
	node2->n_type = NTYPE_DATA;
	node2->data = "aa==ss";
	node2->next = node3;
	node3->n_type = NTYPE_DATA;
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
	node2->n_type = NTYPE_DATA;
	node2->data = "aa";
	node2->next = node3;
	node3->n_type = NTYPE_DATA;
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
	node2->n_type = NTYPE_DATA;
	node2->data = "aa";
	node2->next = node3;
	node3->n_type = NTYPE_DATA;
	node3->data = "kk=aa";
	node3->next = NULL;

	list->start_node = node1;
	return (list);
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;

	// TODO: Temp
	(void)argc;
	(void)argv;
	//

	if (make_info(&info, envp) == -1)
	{
		return (-1);
	}
	while (1)
	{
		str = readline("prompt> ");
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
		else if (str)
		{
			printf("%s\n", str);
		}
		else
		{
			break ;
		}
		add_history(str);
		free(str);
	}
	return (0);
}
