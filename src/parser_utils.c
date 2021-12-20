/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:03:08 by dason             #+#    #+#             */
/*   Updated: 2021/12/20 14:48:12 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	get_ltype(char *s)
{
	if (*s == '|')
		return (LTYPE_PIPE);
	else if (*s == '<' && *(s + 1) == '<')
		return (LTYPE_REDIRECT_L2);
	else if (*s == '<')
		return (LTYPE_REDIRECT_L1);
	else if (*s == '>' && *(s + 1) == '>')
		return (LTYPE_REDIRECT_R2);
	else if (*s == '>')
		return (LTYPE_REDIRECT_R1);
	else
		return (LTYPE_COMMAND);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_ltype_redirect(char *s)
{
	if (*s == '<' && *(s + 1) == '<')
		return (true);
	else if (*s == '>' && *(s + 1) == '>')
		return (true);
	else if (*s == '<')
		return (true);
	else if (*s == '>')
		return (true);
	return (false);
}

int	get_num_of_redirect(char *s)
{
	int		count;
	int		i;
	int		quote;

	count = 0;
	i = -1;
	while (++i < (int)ft_strlen(s))
	{
		if (get_ltype(&s[i]) == LTYPE_REDIRECT_L2 || \
			get_ltype(&s[i]) == LTYPE_REDIRECT_R2)
		{
			i++;
			count++;
		}
		else if (get_ltype(&s[i]) != LTYPE_COMMAND)
			count++;
		if (is_quote(s[i]))
		{
			quote = s[i];
			while (s[++i])
				if (s[i] == quote && i)
					break ;
		}
	}
	return (count);
}

char	*ft_getenv(char **envp, char *env_variable)
{
	char	*env_value;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(env_variable, envp[i], ft_strlen(env_variable)))
		{
			env_value = ft_strdup(&envp[i][ft_strlen(env_variable) + 1]);
			return (env_value);
		}
	}
	return (NULL);
}
