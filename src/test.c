#include "../includes/list_node.h"

void	print_list(t_list *list)
{
	t_node	*node;

	while (list)
	{
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
	while (node)
	{
		printf("--- n_type: %d\n", node->n_type);
		printf("--- data: %s\n", node->data);
		node = node->next;
	}
	printf("\n");
}
