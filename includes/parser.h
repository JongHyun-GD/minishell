/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:48:10 by dason             #+#    #+#             */
/*   Updated: 2021/12/20 14:28:09 by dason            ###   ########.fr       */
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
void	when_quote_organize_node(t_list *list, t_info *info);
void	make_list_no_quote(t_list **list, char **lexer, t_info *info);
int		parser_handling_exception(t_list *list);
int		parser(t_list **list, char *str, t_info *info);

/*
**	UTILS
*/
int		get_ltype(char *s);
bool	is_quote(char c);
bool	is_ltype_redirect(char *s);
int		get_num_of_redirect(char *s);
char	*ft_getenv(char **envp, char *env_variable);

#endif
