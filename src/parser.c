/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:44:18 by dason             #+#    #+#             */
/*   Updated: 2021/11/08 18:18:26 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*organize_str(char *str)
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

int	parser(t_list **list, char *str)
{
	char	**lexer;
	int		i;

	ft_memset(*list, 0, sizeof(t_list));
	str = organize_str(str);
	if (!str)
		return (0);
	lexer = ft_split(str, ' ');
	i = -1;
	while (lexer[++i])
	{
		printf("%s\n", lexer[i]);
	}
	return (1);
}
