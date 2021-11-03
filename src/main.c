#include "../includes/minishell.h"

void	make_info(t_info *info, char **envp)
{
	info->envp = envp;
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	info;

	// TODO: Temp
	argc = 0;
	argv = 0;
	//

	make_info(&info, envp);
	while (1)
	{
		str = readline("prompt> ");
		if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		{
			env(&info);
		}
		else if (str)
		{
			printf("%s\n", str);
		}
		else
		{
			break ;
		}
		add_history(str);
		free(str);
	}
	return (0);
}
