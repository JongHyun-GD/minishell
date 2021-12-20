/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_list_no_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:58:45 by dason             #+#    #+#             */
/*   Updated: 2021/12/20 15:36:25 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static char	*process_get_env_value(char *str, t_info *info, int *i)
{
	char	*env_value;
	char	*env_variable;
	char	*get_env;
	int		len;

	len = 1;
	while (str[len] != '\0' && (ft_isalnum(str[len]) || str[len] == '_' || str[len] == '?'))
		len++;
	if (len == 1)
		return (NULL);
	*i += len;
	env_variable = ft_substr(str, 1, len - 1);
	if (!env_variable)
		exit(1);
	if (*env_variable == '?' && *(env_variable + 1) == '\0')
		env_value = ft_itoa(info->exit_status);
	else
	{
		get_env = ft_getenv(info->envp, env_variable);
		free(env_variable);
		if (get_env == NULL)
			return (NULL);
		env_value = get_env;
	}
	return (env_value);
}

static char	*progress_combine_str(char *lexer, char *str, \
	char *env_value, int *new_i)
{
	char	*new_str;
	size_t	size;

	size = ft_strlen(lexer) + ft_strlen(str) + ft_strlen(env_value) + 1;
	new_str = (char *)calloc(size, sizeof(char));
	if (!new_str)
		exit(1);
	*new_i = ft_strlcat(new_str, str, size) - 1;
	free(str);
	if (env_value != NULL)
	{
		*new_i = ft_strlcat(new_str, env_value, size) - 1;
		free(env_value);
	}
	return (new_str);
}

static char *progress_organize_node(char *lexer, t_info *info)
{
	char	*new_str;
	char	*env_value;
	int		i;
	int		new_i;

	new_str = (char *)calloc(ft_strlen(lexer) + 1, sizeof(char));
	if (!new_str)
		exit(1);
	new_i = -1;
	i = -1;
	while (lexer[++i])
	{
		if (lexer[i] == '$')
		{
			env_value = process_get_env_value(&lexer[i], info, &i);
			new_str = progress_combine_str(lexer, new_str, env_value, &new_i);
		}
		new_str[++new_i] = lexer[i];
	}
	free(lexer);
	return (new_str);
}

static t_list	*progress_create_new_list(char **lexer, int i)
{
	t_list	*new_list;

	if (i != 0 && is_ltype_redirect(lexer[i - 1]))
		new_list = ft_create_list(LTYPE_FILE, \
			ft_create_node(NTYPE_COMMAND, ft_strdup(lexer[i])));
	else
		new_list = ft_create_list(LTYPE_COMMAND, \
			ft_create_node(NTYPE_COMMAND, ft_strdup(lexer[i])));
	return (new_list);
}

void	make_list_no_quote(t_list **list, char **lexer, t_info *info)
{
	t_list	*new_list;
	int		i;

	i = -1;
	while (lexer[++i])
	{
		lexer[i] = progress_organize_node(lexer[i], info);
		if (i == 0 || (get_ltype(lexer[i - 1]) != LTYPE_COMMAND && \
			get_ltype(lexer[i]) == LTYPE_COMMAND))
		{
			new_list = progress_create_new_list(lexer, i);
			if (i == 0)
				*list = new_list;
			else
				ft_lstadd_back(*list, new_list);
		}
		else if (get_ltype(lexer[i]) != LTYPE_COMMAND)
			ft_lstadd_back(*list, ft_create_list(get_ltype(lexer[i]), NULL));
		else
			ft_nodeadd_back(new_list->start_node, \
				ft_create_node(NTYPE_STRING, ft_strdup(lexer[i])));
	}
}
