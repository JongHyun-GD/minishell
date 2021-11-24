/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:48:10 by dason             #+#    #+#             */
/*   Updated: 2021/11/23 22:07:56 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "list_node.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdbool.h>

/*
**	MAIN
*/
void	make_list_quote(t_list **list, char *s);
void	make_list_no_quote(t_list **list, char **lexer);
char	*organize_input_str(char *str);
void	parser_redirect(t_list *list);
void	parser(t_list **list, char *str);

/*
**	UTILS
*/
int		get_l_type(char *s);
bool	is_quote(char c);
bool	is_ltype_redirect(char c);
int		get_num_of_redirect(char *s);

#endif
