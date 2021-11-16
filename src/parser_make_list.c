#include "../includes/parser.h"

// ft_substr, ft_strtrim의 반환이 0일 경우, 처리.
//	ft_create_node의 반환이 return (0); 일 때, 처리
int	make_list_quote(t_list ***list, char *s)
{
	t_list	*new_list;
	int		i;
	int		tmp_i;
// 	char	*tmp_s;

	i = 0;
	while (s[i])
	{
		if (i == 0 || check_l_type(&s[i - 1]))
		{
			tmp_i = i;
			while (s[tmp_i] && !check_l_type(&s[tmp_i]))
				tmp_i++;
			new_list = ft_create_list(LTYPE_COMMAND, NULL);
			if (!new_list)
				return (0);
// 			tmp_s = ft_substr(&s[i], 0, tmp_i - i);
/*			new_list->start_node = ft_create_node(NTYPE_COMMAND, \
				ft_strtrim(tmp_s, " "));	*/
			new_list->start_node = ft_create_node(NTYPE_COMMAND, \
				ft_substr(&s[i], 0, tmp_i - i));
			if (!new_list->start_node)
				return (0);
// 			free(tmp_s);
			if (i == 0)
				**list = new_list;
			else
				ft_listadd_back(**list, new_list);
			i = tmp_i;
		}
		else if (check_l_type(&s[i]) > LTYPE_COMMAND)
			ft_listadd_back(**list, ft_create_list(check_l_type(&s[i++]), NULL));
	}
	return (1);
}

//	ft_create_node의 반환이 return (0); 일 때, 처리
int	make_list_no_quote(t_list ***list, char **lexer)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		if (i == 0 || check_l_type(lexer[i - 1]))
		{
			new_list = ft_create_list(LTYPE_COMMAND, NULL);
			if (!new_list)
				return (0);
			new_list->start_node = ft_create_node(NTYPE_COMMAND, \
				ft_strdup(lexer[i]));
			if (!new_list->start_node)
				return (0);
			if (i == 0)
				**list = new_list;
			else
				ft_listadd_back(**list, new_list);
		}
		else if (check_l_type(lexer[i]) > LTYPE_COMMAND)
			ft_listadd_back(**list, ft_create_list(check_l_type(lexer[i]), NULL));
		else
			ft_nodeadd_back(new_list->start_node, \
					ft_create_node(NTYPE_STRING, ft_strdup(lexer[i])));
	}
	return (1);
}
