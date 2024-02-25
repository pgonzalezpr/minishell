#include "../include/minishell.h"

void	exit_minishell(t_minishell *minishell, char *msg, int status)
{
	clean_minishell(minishell);
	if (msg)
		printf("%s\n", msg);
	exit(status);
}

int	main(void)
{
	t_minishell	minishell;

	ft_memset(&minishell, 0, sizeof(t_minishell));
	while (1)
	{
		minishell.cmd_line = readline(GREEN "minishell$ " DEF_COLOR);
		if (!minishell.cmd_line)
			continue ;
		if (ft_strequals(minishell.cmd_line, "EXIT"))
			exit_minishell(&minishell, NULL, EXIT_SUCCESS);
		//select_builtint(&minishell);
		add_history(minishell.cmd_line);
		if (tokenize_cmd_line(&minishell) == -1 || process_tokens(&minishell)
			== -1 || build_pipeline(&minishell) == -1)
		{
			clean_minishell(&minishell);
			continue ;
		}
		exec_pipeline(&minishell);
		clean_minishell(&minishell);
	}
}
