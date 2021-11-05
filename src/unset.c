/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:16:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/11/05 11:20:29 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	unset(t_list *list, t_info *info)
{
	t_node	*node;
	int		flag;

	node = list->start_node->next;
	while (node)
	{
		if (has_equal(node->data) == false)
		{
			flag = remove_envp(node->data, info->envp, info);
			if (flag == -1)
				return (flag);
		}
		else
		{
			printf("minishell: unset: `%s\': not a valid identifier\n",
				node->data);
		}
		node = node->next;
	}
	return (0);
}
