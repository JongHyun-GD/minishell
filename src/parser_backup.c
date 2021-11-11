#include "../includes/parser.h"

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

static void	make_list(t_list ***list, char **lexer)
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
		else if (check_l_type(lexer[i]) > LTYPE_COMMAND)
			ft_listadd_back(**list, ft_create_list(check_l_type(lexer[i])));
		else
			ft_nodeadd_back(new_list->start_node, \
					ft_create_node(NTYPE_STRING, lexer[i]));
	}
}

static void	organize_quote(t_node *node)
{
	char	*data;
	int		index;
	int		tmp_index;
	int		is_quote;

	data = ft_strdup(node->data);
	index = 0;
	while (data[index])
	{
		if (data[index] == ' ')
		{
			index++;
			continue;
		}
		if (data[index] == 34 || data[index] == 39)
			is_quote = data[index];
		else 
			is_quote = 0;
		tmp_index = index;
		while (data[tmp_index] && is_quote)
		{
			tmp_index++;
			if (data[tmp_index] == is_quote)
			{
				tmp_index++;
				break ;
			}
		}
		while (data[tmp_index] && !is_quote)
		{
			tmp_index++;
			if (data[tmp_index] == 34 || data[tmp_index] == 39)
				break ;
		}
		printf("index: %d\n", index);
		printf("tmp_index: %d\n", tmp_index);
		printf("len: %d\n", tmp_index - index);
		printf("&data[%d]: %s\n", index, &data[index]);
		if (index == 0)
		{
			free(node->data);
			node->data = ft_substr(&data[index], 0, tmp_index - index);
		}
		else 
			ft_nodeadd_back(node, ft_create_node(NTYPE_STRING, ft_substr(&data[index], 0, tmp_index - index)));
		index += (tmp_index - index);
		printf("\n");
	}
	free(data);
}

static void	merge_node(t_node *node)
{
	t_node	*next_node;
	char	*tmp_s;
	char	*data;

	while (node->next)
	{
		next_node = node->next;
		tmp_s = ft_strjoin(node->data, " ");
		free(node->data);
		data = ft_strjoin(tmp_s, next_node->data);
		free(tmp_s);
		node->data = data;
		node->next = next_node->next;
		free(next_node->data);
		free(next_node);
	}
}

static void	organize_data_in_node(t_list *list)
{
	t_node	*node;
	char	*d_quote;
	char	*s_quote;

	while (list)
	{
		node = list->start_node;
		while (node)
		{
			d_quote = ft_strchr(node->data, 34);
			s_quote = ft_strchr(node->data, 39);
			if (d_quote || s_quote)
			{
				merge_node(node);
				organize_quote(node);
				break ;
			}
			node = node->next;
		}
		list = list->next;
	}
}




int	parser(t_info info, t_list **list, char *str)
{
	char	**lexer;

	(void)info;
	str = organize_str(str);
	if (!str)
		return (0);
	make_list(&list, lexer);
	organize_data_in_node(*list);
	free(str);
	free_double_pointer(&lexer);
	return (0);
}
