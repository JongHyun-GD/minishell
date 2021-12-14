/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_list_no_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:58:45 by dason             #+#    #+#             */
/*   Updated: 2021/12/13 19:15:01 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	process_variable(char **str, t_info *info)
{
	char	*new_str;
	char	*env_variable;
	char	*get_env;

	env_variable = ft_substr(*str, 1, ft_strlen(*str));
	if (!env_variable)
		exit(1);
	if (*env_variable == '?' && *(env_variable + 1) == '\0')
		new_str = ft_itoa(info->exit_status);
	else
	{
		get_env = getenv(env_variable);
		free(env_variable);
		if (!get_env)
			return ;
		new_str = ft_strdup(get_env);
	}
	free(*str);
	*str = new_str;
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
		if (lexer[i][0] == '$')
			process_variable(&lexer[i], info);
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
