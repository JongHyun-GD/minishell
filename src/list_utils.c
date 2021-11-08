#include "../includes/minishell.h"

t_node	*ft_create_node(int n_type, char *data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (0);
	ft_memset(new_node, 0, sizeof(t_node));
	new_node->n_type = n_type;
	new_node->data = data;
	return (new_node);
}

t_list	*ft_create_list(int l_type)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (0);
	ft_memset(new_list, 0, sizeof(t_list));
	new_list->l_type = l_type;
	return (new_list);
}

void	ft_nodeadd_back(t_node *node, t_node *new_node)
{
	while (node->next)
		node = node->next;
	node->next = new_node;
}

void	ft_listadd_back(t_list *list, t_list *new_list)
{
	while (list->next)
		list = list->next;
	list->next = new_list;
}

/* TEST */
void	print_list(t_list *list)
{
	printf("## print_list\n");
	t_node	*node;

	while (list)
	{
		printf("-l_type: %d\n", list->l_type);
		node = list->start_node;
		while(node)
		{
			printf("--n_type: %d\n", node->n_type);
			printf("--data: %s\n", node->data);
			node = node->next;
		}
		printf("\n");
		list = list->next;
		printf("\n");
	}
}
