/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:48:10 by dason             #+#    #+#             */
/*   Updated: 2021/12/04 12:48:28 by dason            ###   ########.fr       */
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

char	*organize_input_str(char *str);
void	make_list_quote(t_list **list, char *s);
void	make_list_no_quote(t_list **list, char **lexer);
void	organize_node(t_list *list);
int		parser_handling_exception(t_list *list);
int		parser(t_list **list, char *str);

/*
**	UTILS
*/
int		get_ltype(char *s);
bool	is_quote(char c);
bool	is_ltype_redirect(char *);
int		get_num_of_redirect(char *s);

#endif
