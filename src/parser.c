#include "../includes/parser.h"

static int	organize_data(t_node *node)
{
	t_node	*new_node;
	t_node	*next_node;
	char	*data;
	char	*sub_data;
	int		i;
	int		len;
	int		is_quote;

	data = ft_strtrim(node->data, " ");
	if (!data)
		return (0);
	is_quote = 0;
	i = 0;
	while (data[i])
	{
		while (data[i] == ' ')
			i++;
		len = 0;
		while (data[i + len] && (data[i + len] != ' ' && \
				data[i + len] != 34 && data[i + len] != 39))
			len++;
		if (data[i + len] == 34 || data[i + len] == 39)
		{
			is_quote = data[i + len++];
			while (data[i + len] && data[i + len] != is_quote)
				len++;
			len++;
			while (data[i + len] && data[i + len] != ' ')
				len++;
			is_quote = 0;
		}
		sub_data = ft_substr(data, i, len);
		new_node = ft_create_node(NTYPE_STRING, sub_data);
		if (!new_node)
			return (0);
		ft_nodeadd_back(node, new_node);
		i += len;
	}
	next_node = node->next;
	free(node->data);
	node->data = next_node->data;
	node->next = next_node->next;
	free(next_node);
	return (1);
}

static int	organize_node(t_node *node)
{
	char	*new_data;
	char	*d_quote;
	char	*s_quote;

	while (node)
	{
		if (ft_strchr(node->data, 34) || ft_strchr(node->data, 39))
		{
			d_quote = ft_strchr(node->data, 34);
			s_quote = ft_strchr(node->data, 39);
			if ((d_quote && !s_quote) || (d_quote && s_quote && d_quote < s_quote))
			{
				node->n_type = NTYPE_VARIABLE;
				new_data = remove_c_copy(node->data, 34, \
					get_num_of_c(node->data, 34));
			}
			else if ((!d_quote && s_quote) || (d_quote && s_quote && d_quote > s_quote))
				new_data = remove_c_copy(node->data, 39, \
					get_num_of_c(node->data, 39));
			free(node->data);
			node->data = new_data;
		}
		node = node->next;
	}
	return (1);
}

//	TODO: $가 있으면 NTYPE_VARIABLE
int	parser(t_list **list, char *str)
{
	char	**lexer;
	t_list	*tmp_list;

	printf("str: %s\n", str);
	str = organize_input_str(str);
	if (!str)
		return (0);
	if (ft_strchr(str, 34) || ft_strchr(str, 39))
	{
		if (!make_list_quote(&list, str))
			return (0);
		tmp_list = *list;
		while (tmp_list)
		{
			if (tmp_list->l_type == LTYPE_COMMAND)
			{
				if (!organize_data(tmp_list->start_node))
					return (0);
				if (!organize_node(tmp_list->start_node))
					return (0);
			}
			tmp_list = tmp_list->next;
		}
	}
	else
	{
		lexer = ft_split(str, ' ');
		if (!lexer)
			return (0);
		if (!make_list_no_quote(&list, lexer))
			return (0);
		free_double_pointer(&lexer);
	}
	free(str);
	return (1);
}
