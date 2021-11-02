#include <minishell.h>

int main(void)
{
	char	*str;

	while (1)
	{
		str = readline("prompt> ");
		if (str)
		{
			printf("%s\n", str);
		}
		else if (ft_strncmp(str, "env", ft_strlen(str)) == 0) {
			char **envp = get_envp();
			while (*envp) {
				printf("%s\n", *envp);
				*envp++;
			}
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
