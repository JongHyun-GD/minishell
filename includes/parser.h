/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:12:17 by dason             #+#    #+#             */
/*   Updated: 2021/11/11 14:12:18 by dason            ###   ########.fr       */
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
char	*organize_str(char *str);
int		parser(t_info info, t_list **list, char *str);

/*
**	UTILS
*/
int		get_num_of_c(char *s, char c);

#endif
