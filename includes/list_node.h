/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:09:01 by dason             #+#    #+#             */
/*   Updated: 2021/11/23 21:27:45 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_NODE_H
# define LIST_NODE_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>

# define NTYPE_NONE 0
# define NTYPE_COMMAND 1
# define NTYPE_VARIABLE 2
# define NTYPE_STRING 3

# define LTYPE_NONE 0
# define LTYPE_COMMAND 1
# define LTYPE_PIPE 2
# define LTYPE_REDIRECT_L 3
# define LTYPE_REDIRECT2_L 4
# define LTYPE_REDIRECT_R 5
# define LTYPE_REDIRECT2_R 6

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

t_list	*ft_create_list(int l_type, t_node *start_node);
t_node	*ft_create_node(int n_type, char *data);
void	ft_lstadd_back(t_list *list, t_list *new_list);
void	ft_nodeadd_back(t_node *node, t_node *new_node);
void	free_list_node(t_list *list);

/*
**	TEST
*/
void	print_list(t_list *list);
void	print_node(t_node *node);

#endif
