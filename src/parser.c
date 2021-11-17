/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:30:26 by dason             #+#    #+#             */
/*   Updated: 2021/11/17 16:42:52 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	get_len_when_quote(char *data, int i, int len)
{
	int	is_quote;

	is_quote = data[i + len++];
	while (data[i + len] && data[i + len] != is_quote)
		len++;
	len++;
	while (data[i + len] && data[i + len] != ' ')
		len++;
	is_quote = 0;
	return (len);
}

static void	organize_data(t_list *list)
{
	char	*data;
	int		i;
	int		len;

	data = ft_strtrim(list->start_node->data, " ");
	if (!data)
		exit(1);
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
			len = get_len_when_quote(data, i, len);
		ft_nodeadd_back(list->start_node, \
			ft_create_node(NTYPE_STRING, ft_substr(data, i, len)));
		i += len;
	}
	free(data);
}

static void	organize_node(t_node *node)
{
	char	*new_data;
	int		is_quote;
	int		size;

	while (node)
	{
		is_quote = check_quote(node->data);
		if (is_quote)
		{
			size = get_num_of_c(node->data, is_quote);
			if (is_quote == 34)
			{
				node->n_type = NTYPE_VARIABLE;
				new_data = remove_c_copy(node->data, 34, size);
			}
			else if (is_quote == 39)
				new_data = remove_c_copy(node->data, 39, size);
			free(node->data);
			node->data = new_data;
		}
		node = node->next;
	}
}

static int	organize_list(t_list *list)
{
	t_node	*next_node;

	while (list)
	{
		if (list->l_type == LTYPE_COMMAND)
		{
			organize_data(list);
			next_node = list->start_node->next;
			free(list->start_node->data);
			free(list->start_node);
			list->start_node = next_node;
			list->start_node->n_type = NTYPE_COMMAND;
			organize_node(list->start_node);
		}
		list = list->next;
	}
	return (1);
}

int	parser(t_list **list, char *str)
{
	char	**lexer;

	str = organize_input_str(str);
	if (ft_strchr(str, 34) || ft_strchr(str, 39))
	{
		make_list_quote(list, str);
		organize_list(*list);
	}
	else
	{
		lexer = ft_split(str, ' ');
		if (!lexer)
			exit(1);
		make_list_no_quote(list, lexer);
		free_double_pointer(&lexer);
	}
	free(str);
	return (1);
}
