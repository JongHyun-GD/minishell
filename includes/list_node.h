/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:47:38 by dason             #+#    #+#             */
/*   Updated: 2021/11/08 17:47:58 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_NODE_H
# define LIST_NODE_H

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

#endif
