/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:41:12 by dason             #+#    #+#             */
/*   Updated: 2021/11/10 09:34:11 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/list_node.h"

t_node	*ft_create_node(int n_type, char *data)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->n_type = n_type;
	new_node->data = ft_strdup(data);
	return (new_node);
}

t_list	*ft_create_list(int l_type)
{
	t_list	*new_list;

	new_list = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_list)
		return (0);
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

void	free_list_node(t_list *list)
{
	t_list	*next_list;
	t_node	*node;
	t_node	*next_node;

	while (list->next)
	{
		node = list->start_node;
		while (node && node->next)
		{
			next_node = node->next;
			free(node->data);
			free(node);
			node = next_node;
		}
		if (node)
		{
			free(node->data);
			free(node);
		}
		next_list = list->next;
		free(list);
		list = next_list;
	}
	free(list);
}
