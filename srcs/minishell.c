#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_memset(&minishell, 0, sizeof(minishell));
		if (init_env(env, &minishell) != SUCCESS)
			return (EXIT_FAILURE);
		minishell.cmd_line = readline(GREEN "minishell$ " DEF_COLOR);
		if (!minishell.cmd_line)
			continue ;
		if (!*minishell.cmd_line)
		{
			free(minishell.cmd_line);
			continue ;
		}
		select_builtint(&minishell);
		add_history(minishell.cmd_line);
		//parse_cmd_line(&minishell);
		build_pipeline(&minishell);
		exec_pipeline(&minishell);
		clean_minishell(&minishell);
	}
	return (0);
}
