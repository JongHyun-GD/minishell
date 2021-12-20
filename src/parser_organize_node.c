/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organize_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:09:19 by dason             #+#    #+#             */
/*   Updated: 2021/12/20 14:37:16 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static char	*get_env_value(char *s, int *i, t_info *info)
{
	char	*env_variable;
	char	*env_value;
	int		len;

	len = 0;
	while (s[++len])
	{
		if (s[len] == ' ' || s[len] == '\"' || s[len] == '\'')
			break ;
	}
	*i += (len - 1);
	env_variable = ft_substr(s, 1, len - 1);
	if (*env_variable == '?')
		env_value = ft_itoa(info->exit_status);
	else
	{
		env_value = ft_strdup(ft_getenv(info->envp, env_variable));
		if (env_value == NULL)
			env_value = ft_strdup("");
	}
	free(env_variable);
	return (env_value);
}

static char	*combine_nodedata_env(char *data, int *i, int *new_i, t_info *info)
{
	char	*new_data;
	char	*env_value;
	size_t	size;

	env_value = get_env_value(&data[*i], i, info);
	size = ft_strlen(data) + \
		   ft_strlen(env_value) + ft_strlen(info->current_node->data);
	new_data = (char *)ft_calloc(size, sizeof(char));
	if (!new_data)
		exit(1);
	ft_strlcat(new_data, info->current_node->data, \
		ft_strlen(info->current_node->data) + 1);
	ft_strlcat(new_data, env_value, size);
	free(env_value);
	(*new_i) = ft_strlen(new_data);
	return (new_data);
}

static void	process_quote_in_node(char *data, int *i, int *new_i, t_info *info)
{
	char	*new_data;
	int		quote;

	quote = data[*i];
	while (data[++(*i)])
	{
		if (data[*i] == quote)
			break ;
		if (quote == '\"' && data[*i] == '$')
		{
			new_data = combine_nodedata_env(data, i, new_i, info);
			free(info->current_node->data);
			info->current_node->data = new_data;
		}
		else if (data[*i] != quote)
			info->current_node->data[(*new_i)++] = data[*i];
	}
}

void	when_quote_organize_node(t_list *list, t_info *info)
{
	char	*data;
	int		i;
	int		new_i;

	info->current_node = list->start_node;
	data = ft_strdup(list->start_node->data);
	ft_memset(info->current_node->data, 0, ft_strlen(info->current_node->data));
	i = -1;
	new_i = 0;
	while (data[++i])
	{
		if (is_quote(data[i]) == false && data[i] != ' ')
			info->current_node->data[new_i++] = data[i];
		else if (data[i] == ' ')
		{
			info->current_node->next = ft_create_node(NTYPE_STRING, \
					(char *)ft_calloc(ft_strlen(data) + 1, sizeof(char)));
			info->current_node = info->current_node->next;
			new_i = 0;
		}
		else if (is_quote(data[i]))
			process_quote_in_node(data, &i, &new_i, info);
	}
	free(data);
}
