#include "../includes/minishell.h"

void	make_info(t_info *info, char **envp)
{
	info->envp = envp;
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;
	t_list	*list;

	(void)argc;
	(void)argv;
	make_info(&info, envp);
	while (1)
	{
		str = readline("prompt> ");
		parser(&list, ft_strdup(str));
		if (!str)
			return (-1);
		if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		{
			env(&info);
		}
		else if (!(ft_strncmp(str, "quit", ft_strlen(str))))
		{
			free(str);
			break ;
		}
		else if (str)
		{
			printf("%s\n", str);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
