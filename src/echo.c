/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:31:57 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/08 10:48:01 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/echo.h"

int	echo(t_list *list)
{
	bool	has_n_flag;
	t_node	*node;

	if (!list || list->l_type != LTYPE_COMMAND) return (-1);

	has_n_flag = false;
	node = list->start_node;
	while (node)
	{
		if (ft_strlen(node->data) == 2 &&
			node->data[0] == '-' && node->data[1] == 'n')
			has_n_flag = true;
		else
			printf("%s", node->data);
		node = node->next;
	}
	if (has_n_flag == false)
		printf("\n");
}
