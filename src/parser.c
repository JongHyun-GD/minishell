/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:54:56 by dason             #+#    #+#             */
/*   Updated: 2021/11/09 14:54:57 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static char	*organize_str(char *str)
{
	char	*tmp;

	if (ft_strchr(str, '|'))
		str = str_split_recomb(str, '|', false);
	if (ft_strchr(str, ';'))
		str = str_split_recomb(str, ';', false);
	tmp = ft_strchr(str, '<');
	if (tmp)
	{
		if (*(tmp + 1) != '<')
			str = str_split_recomb(str, '<', false);
		else
			str = str_split_recomb(str, '<', true);
	}
	tmp = ft_strchr(str, '>');
	if (tmp)
	{
		if (*(tmp + 1) != '>')
			str = str_split_recomb(str, '>', false);
		else
			str = str_split_recomb(str, '>', true);
	}
	if (!str)
		return (NULL);
	return (str);
}

static int	check_l_type(char *s)
{
	if (!ft_strncmp(s, "|", ft_strlen(s)))
		return (LTYPE_PIPE);
	if (!ft_strncmp(s, ";", ft_strlen(s)))
		return (LTYPE_SEMI_COLON);
	if (!ft_strncmp(s, "<", ft_strlen(s)))
		return (LTYPE_REDIRECT);
	if (!ft_strncmp(s, ">", ft_strlen(s)))
		return (LTYPE_REDIRECT);
	if (!ft_strncmp(s, "<<", ft_strlen(s)))
		return (LTYPE_REDIRECT);
	if (!ft_strncmp(s, ">>", ft_strlen(s)))
		return (LTYPE_REDIRECT);
	return (0);
}

static void	put_the_struct(t_list ***list, char **lexer)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		if (i == 0 || check_l_type(lexer[i - 1]))
		{
			new_list = ft_create_list(LTYPE_COMMAND);
			new_list->start_node = ft_create_node(NTYPE_COMMAND, lexer[i]);
			if (i == 0)
				**list = new_list;
			else
				ft_listadd_back(**list, new_list);
		}
		else
		{
			if (check_l_type(lexer[i]) > LTYPE_COMMAND)
				ft_listadd_back(**list, ft_create_list(check_l_type(lexer[i])));
			else
				ft_nodeadd_back(new_list->start_node, \
					ft_create_node(NTYPE_STRING, lexer[i]));
		}
	}
}

int	parser(t_list **list, char *str)
{
	char	**lexer;

	str = organize_str(str);
	if (!str)
		return (0);
	lexer = ft_split(str, ' ');
	put_the_struct(&list, lexer);
	free(str);
	free_double_pointer(&lexer);
	return (0);
}
