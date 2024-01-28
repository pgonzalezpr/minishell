#include "../include/minishell.h"

int	main(void)
{
	t_minishell	minishell;

	while (1)
	{
		ft_memset(&minishell, 0, sizeof(minishell));
		minishell.cmd_line = readline("minishell$ ");
		if (!minishell.cmd_line)
			continue ;
		if (!*minishell.cmd_line)
		{
			free(minishell.cmd_line);
			continue ;
		}
		if (ft_strncmp(minishell.cmd_line, "exit", 4) == 0)
		{
			rl_clear_history();
			exit_minishell(&minishell, NULL, EXIT_SUCCESS);
		}
		add_history(minishell.cmd_line);
		parse_cmd_line(&minishell);
		build_pipeline(&minishell);
		exec_pipeline(&minishell);
		clean_minishell(&minishell);
	}
	return (0);
}
