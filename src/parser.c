#include "../includes/parser.h"

static char	*get_env_variable(char *s, int *i)
{
	char	*env;
	int		len;

	len = 0;
	while (s[++len])
	{
		if (s[len] == ' ' || s[len] == '\"' || s[len] == '\'')
			break ;
	}
	env = ft_substr(s, 1, len - 1);
	*i += (len - 1);
	return (env);
}

static void	process_quote_in_node(t_node *node, char *data, int *i, int *new_i)
{
	int		quote;
	char	*env_variable;
	char	*env_value;
	char	*new_data;

	quote = data[*i];
	while (data[++(*i)])
	{
		if (data[*i] == quote)
			break ;
		if (quote == '\"' && data[*i] == '$')
		{
			env_variable = get_env_variable(&data[*i], i);
			env_value = getenv(env_variable);
			new_data = (char *)ft_calloc(ft_strlen(data) + \
				ft_strlen(env_value) + ft_strlen(node->data), sizeof(char));
			if (!new_data)
				exit(1);
			ft_strlcat(new_data, node->data, ft_strlen(node->data) + 1);
			ft_strlcat(new_data, env_value, ft_strlen(node->data) + 1 + ft_strlen(env_value) + 1);
			free(node->data);
			node->data = new_data;
			(*new_i) += ft_strlen(env_value);
			free(env_variable);
		}
		else if (data[*i] != quote)
			node->data[(*new_i)++] = data[*i];
	}
}

static void	organize_node(t_list *list)
{
	t_node	*current_node;
	char	*data;
	int		i;
	int		new_i;

	current_node = list->start_node;
	data = ft_strdup(list->start_node->data);
	ft_memset(current_node->data, 0, ft_strlen(current_node->data));
	i = -1;
	new_i = 0;
	while (data[++i])
	{
		if (is_quote(data[i]) == false && data[i] != ' ')
			current_node->data[new_i++] = data[i];
		else if (data[i] == ' ')
		{
			current_node->next = ft_create_node(NTYPE_STRING, \
					(char *)ft_calloc(ft_strlen(data) + 1, sizeof(char)));
			current_node = current_node->next;
			new_i = 0;
		}
		else if (is_quote(data[i]))
			process_quote_in_node(current_node, data, &i, &new_i);
	}
	free(data);
}

static void	organize_list(t_list *list)
{

	while (list)
	{
		if (list->l_type == LTYPE_COMMAND)
			organize_node(list);
		list = list->next;
	}
}

int	parser(t_list **list, char *str)
{
	char	**lexer;

	str = organize_input_str(str);
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
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
