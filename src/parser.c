#include "../includes/parser.h"

//	TODO: ft_create_list, ft_create_node가 return (0); 인 경우, 처리
static int	make_list_quote(t_list ***list, char *s)
{
	t_list	*new_list;
	int		i;
	int		tmp_i;

	i = 0;
	while (s[i])
	{
		if (i == 0 || check_l_type(&s[i - 1]))
		{
			tmp_i = i;
			while (s[tmp_i] && !check_l_type(&s[tmp_i]))
				tmp_i++;
			new_list = ft_create_list(LTYPE_COMMAND);
			new_list->start_node = ft_create_node(NTYPE_COMMAND, \
				ft_substr(&s[i], 0, tmp_i - i));
			if (i == 0)
				**list = new_list;
			else if (s[i + 1] != '\0')
				ft_listadd_back(**list, new_list);
			i = tmp_i;
		}
		else if (check_l_type(&s[i]) > LTYPE_COMMAND)
			ft_listadd_back(**list, ft_create_list(check_l_type(&s[i++])));
	}
	return (1);
}

// TODO: ft_create_list, ft_create_node가 return (0); 인 경우, 처리
static void	make_list_no_quote(t_list ***list, char **lexer)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		if (i == 0 || check_l_type(lexer[i - 1]))
		{
			new_list = ft_create_list(LTYPE_COMMAND);
			new_list->start_node = ft_create_node(NTYPE_COMMAND, \
				ft_strdup(lexer[i]));
			if (i == 0)
				**list = new_list;
			else
				ft_listadd_back(**list, new_list);
		}
		else if (check_l_type(lexer[i]) > LTYPE_COMMAND)
			ft_listadd_back(**list, ft_create_list(check_l_type(lexer[i])));
		else
			ft_nodeadd_back(new_list->start_node, \
					ft_create_node(NTYPE_STRING, ft_strdup(lexer[i])));
	}
}

// static void	organize_quote(t_node *node)
// {
// 	char	*data;
// 	int		index;
// 	int		tmp_index;
// 	int		is_quote;
// 
// 	data = ft_strdup(node->data);
// 	index = 0;
// 	while (data[index])
// 	{
// 		if (data[index] == ' ')
// 		{
// 			index++;
// 			continue;
// 		}
// 		if (data[index] == 34 || data[index] == 39)
// 			is_quote = data[index];
// 		else 
// 			is_quote = 0;
// 		tmp_index = index;
// 		while (data[tmp_index] && is_quote)
// 		{
// 			tmp_index++;
// 			if (data[tmp_index] == is_quote)
// 			{
// 				tmp_index++;
// 				break ;
// 			}
// 		}
// 		while (data[tmp_index] && !is_quote)
// 		{
// 			tmp_index++;
// 			if (data[tmp_index] == 34 || data[tmp_index] == 39)
// 				break ;
// 		}
// 		printf("index: %d\n", index);
// 		printf("tmp_index: %d\n", tmp_index);
// 		printf("len: %d\n", tmp_index - index);
// 		printf("&data[%d]: %s\n", index, &data[index]);
// 		if (index == 0)
// 		{
// 			free(node->data);
// 			node->data = ft_substr(&data[index], 0, tmp_index - index);
// 		}
// 		else 
// 			ft_nodeadd_back(node, ft_create_node(NTYPE_STRING, ft_substr(&data[index], 0, tmp_index - index)));
// 		index += (tmp_index - index);
// 		printf("\n");
// 	}
// 	free(data);
// }

//	TODO: $가 있으면 NTYPE_VARIABLE
int	parser(t_info info, t_list **list, char *str)
{
	char	**lexer;
	(void)info;

	str = organize_str(str);
	if (!str)
		return (0);
	if (ft_strchr(str, 34) || ft_strchr(str, 39))
	{
		make_list_quote(&list, str);
	}
	else
	{
		lexer = ft_split(str, ' ');
		make_list_no_quote(&list, lexer);
		free_double_pointer(&lexer);
	}
	free(str);
	return (1);
}
