#include "../includes/parser.h"

int     get_num_of_c(char *s, char c)
{
	int             index;
	int             count;

	count = 0;
	index = -1;
	while (s[++index])
	{
		if (s[index] == c)
			count++;
	}
	return (count);
}

int     check_l_type(char *s)
{
	if (*s == '|')
		return (LTYPE_PIPE);
	if (*s == ';')
		return (LTYPE_SEMI_COLON);
	if (*s == '<')
		return (LTYPE_REDIRECT);
	if (*s == '>')
		return (LTYPE_REDIRECT);
	if (*s == '<' && *(s + 1) == '<')
		return (LTYPE_REDIRECT);
	if (*s == '>' && *(s + 1) == '>')
		return (LTYPE_REDIRECT);
	return (0);
}

char	*remove_c_copy(char *data, int c, int size)
{
	char	*new_data;
	char	*first_c;
	char	*last_c;
	int		i;
	int		new_data_i;

	new_data = (char *)ft_calloc(ft_strlen(data) - size + 1, sizeof(char));
	first_c = ft_strchr(data, c);
	last_c = ft_strrchr(data, c);
	new_data_i = -1;
	i = -1;
	while (data[++i])
	{
		if (&data[i] == first_c || &data[i] == last_c)
			continue;
		new_data[++new_data_i] = data[i];
	}
	return (new_data);
}
