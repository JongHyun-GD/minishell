/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:48:10 by dason             #+#    #+#             */
/*   Updated: 2021/11/18 14:46:47 by dason            ###   ########.fr       */
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
int		parser(t_list **list, char *str);

/*
**	UTILS
*/
int		get_num_of_c(char *s, char c);
int		get_l_type(char *s);
char	*remove_char_in_str(char *data, int c);
int		check_quote(char *data);
bool	is_quote(char c);

#endif
