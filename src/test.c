#include "../includes/list_node.h"
#include "../includes/minishell.h"

char	*get_eof_input(void)
{
	char	*buf;
	char	*res;

	res = readline("heredoc> ");
	if (res == NULL)
	{
		exit(1);
	}
	buf = ft_strjoin(res, "\n");
	return (buf);
}

void	print_list(t_list *list)
{
	t_node	*node;

	printf("### print_list\n");
	if (!list)
	{
		printf("NULL list\n");
		return ;
	}
	while (list)
	{
		printf("- prev adrees: %p\n", list->prev);
		printf("- current adrees: %p\n", list);
		printf("- next adrees: %p\n", list->next);
		printf("- l_type: %d\n", list->l_type);
		node = list->start_node;
		while (node)
		{
			printf("-- n_type: %d\n", node->n_type);
			printf("-- data: %s\n", node->data);
			node = node->next;
		}
		printf("\n");
		list = list->next;
	}
}

void	print_node(t_node *node)
{
	printf("### print_node\n");
	if (!node)
	{
		printf("NULL node\n");
		return ;
	}
	while (node)
	{
		printf("- n_type: %d\n", node->n_type);
		printf("- data: %s\n", node->data);
		node = node->next;
	}
	printf("\n");
}
