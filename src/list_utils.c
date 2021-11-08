/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:36:05 by dason             #+#    #+#             */
/*   Updated: 2021/11/08 18:36:20 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
