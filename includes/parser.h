/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:12:17 by dason             #+#    #+#             */
/*   Updated: 2021/11/16 14:16:28 by dason            ###   ########.fr       */
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
int		make_list_quote(t_list ***list, char *s);
int		make_list_no_quote(t_list ***list, char **lexer);
char	*organize_input_str(char *str);
int		parser(t_list **list, char *str);

/*
**	UTILS
*/
int		get_num_of_c(char *s, char c);
int		check_l_type(char *s);
char	*remove_c_copy(char *data, int c, int size);

#endif
