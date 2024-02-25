#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* STRUCTS */
typedef struct s_command_node	t_command_node;
typedef struct s_token_node		t_token_node;

typedef struct s_command_node
{
	t_command_node				*next;
}								t_command_node;

typedef struct s_token_node
{
	char						*token;
	t_token_node				*next;
}								t_token_node;

typedef struct s_minishell
{
	char						*cmd_line;
	t_token_node				*tokens;
	t_command_node				*pipeline;
	size_t						cmd_count;
	int							**pipes;
	int							**here_doc_pipes;
	int							last_exit_code;

}								t_minishell;

/* COLORS */
# define GREEN "\033[0;92m"
# define DEF_COLOR "\033[0;39m"

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define EMPTY ' '
# define LINE_BREAK '\n'

/* BUILT INS (COMMANDS) */
# define EXIT_CMD_NOT_FOUND 127
# define MALLOC_ERR_MSG "Allocation error"
# define UNCLOSED_QUOTE_MSG "Error. Unclosed quote"
# define EXIT_CMD "exit"
# define ECHO_CMD "echo"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define EXPORT_CMD "export"
# define UNSET_CMD "unset"
# define ENV_CMD "env"
# define FLAG_N "-n"

/* PROTOTYPES */
int								tokenize_cmd_line(t_minishell *minishell);
int								process_tokens(t_minishell *minishell);
void							remove_quotes(char *token);
char							*substring(char *start, char *end);
int								ft_strequals(char *s1, char *s2);
char							*expand_token(char *token,
									t_minishell *minishell);
int								build_pipeline(t_minishell *minishell);
void							exec_pipeline(t_minishell *minishell);
void							clean_minishell(t_minishell *minishell);
void							exit_minishell(t_minishell *minishell,
									char *msg, int status);
void							free_tokens(t_token_node *tokens);
void							free_pipeline(t_command_node *pipeline);
void							free_pipe_arr(int **arr, size_t size);

/* BUILT-INS */
void							select_builtint(t_minishell *minishell);
void							echo_cmd(char **cmd);
void							export_cmd(t_minishell *minishell);
void							cd_cmd(t_minishell *minishell);
void							unset_cmd(t_minishell *minishell);
void							env_cmd(t_minishell *minishell);
void							pwd_cmd(t_minishell *minishell);

#endif