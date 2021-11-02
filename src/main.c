#include <minishell.h>

int	main(void)
{
	char	*str;
	char	**argv;
	char	**envp;

	while (1)
	{
		str = readline("prompt> ");
		if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		{
			argv = 0;
			envp = get_envp();
			execve(ENV_PATH, argv, envp);
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
