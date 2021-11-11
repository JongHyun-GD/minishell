/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:29 by hyun              #+#    #+#             */
/*   Updated: 2021/11/11 09:29:46 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_NODE_H
# define LIST_NODE_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>

# define NTYPE_NONE 0
# define NTYPE_COMMAND 1
# define NTYPE_FLAG 2
# define NTYPE_STRING 3

# define LTYPE_NONE 0
# define LTYPE_COMMAND 1
# define LTYPE_PIPE 2
# define LTYPE_SEMI_COLON 3
# define LTYPE_REDIRECT 4

typedef struct s_node
{
	int				n_type;
	char			*data;
	struct s_node	*next;
}					t_node;

typedef struct s_list
{
	int				l_type;
	struct s_node	*start_node;
	struct s_list	*next;
}					t_list;

t_node	*ft_create_node(int n_type, char *data);
t_list	*ft_create_list(int l_type);
void	ft_nodeadd_back(t_node *node, t_node *new_list);
void	ft_listadd_back(t_list *list, t_list *new_list);
void	free_list_node(t_list *list);

/*
**	TEST
*/
void	print_list(t_list *list);

#endif
