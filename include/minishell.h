#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_command_node	t_command_node;

typedef struct s_minishell
{
	char						*cmd_line;
	char						**tokens;
	t_command_node				*pipeline;
	size_t						cmd_count;
	int							**pipes;
	int							**here_doc_pipes;

}								t_minishell;

typedef struct s_command_node
{
	t_command_node				*next;
}								t_command_node;

# define EXIT_CMD_NOT_FOUND 127

void							parse_cmd_line(t_minishell *minishell);
void							build_pipeline(t_minishell *minishell);
void							exec_pipeline(t_minishell *minishell);
void							clean_minishell(t_minishell *minishell);
void							exit_minishell(t_minishell *minishell,
									char *msg, int status);

#endif