/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organize_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:41:36 by dason             #+#    #+#             */
/*   Updated: 2021/11/23 23:03:58 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

// redirection 처리
// redirection 앞 뒤에 스페이스 있을 때 처리
char	*organize_input_str(char *str)
{
	char	*new_str;
	int		count_ltype;
	int		i;
	int		quote;
	int		new_i;

	count_ltype = get_num_of_ltype(str);
	printf("strlen(str): %lu\n", ft_strlen(str));
	printf("count_ltype: %d\n", count_ltype);
	printf("size: %lu\n", ft_strlen(str) + count_ltype * 2 + 1);
	new_str = (char *)ft_calloc(ft_strlen(str) + count_ltype * 2 + 1, sizeof(char));
	if (!new_str)
		exit(1);
	new_i = 0;
	i = -1;
	while (++i < (int)ft_strlen(str) + 1)
	{
		if (str[i] == ' ')
		{
			new_str[new_i++] = ' ';
			while (str[++i] == ' ')
			{
			}
		}
		if ((str[i] == ' ' && get_l_type(&str[i + 1]) != LTYPE_COMMAND) || 
			(str[i] == ' ' && get_l_type(&str[i - 1]) != LTYPE_COMMAND))
			continue ;
		if (get_l_type(&str[i]) == LTYPE_REDIRECT2_L ||
			get_l_type(&str[i]) == LTYPE_REDIRECT2_R)
		{
			new_str[new_i++] = ' ';
			new_str[new_i++] = str[i++];
			new_str[new_i++] = str[i++];
			if (str[i + 1] != ' ')
				new_str[new_i++] = ' ';
		}
		else if (get_l_type(&str[i]) != LTYPE_COMMAND)
		{
			new_str[new_i++] = ' ';
			new_str[new_i++] = str[i++];
			if (str[i + 1] != ' ')
				new_str[new_i++] = ' ';
		}
		else if (is_quote(str[i]))
		{
			quote = str[i];
			while (str[i])
			{
				new_str[new_i++] = str[i++];
				if (str[i] == quote)
					break ;
			}
		}
		new_str[new_i++] = str[i];
	}
	printf("new_str: %s\n", new_str);
	printf("strlen(new_str): %lu\n", ft_strlen(new_str));
	free(str);
	return (new_str);
}
