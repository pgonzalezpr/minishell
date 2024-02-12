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

typedef struct s_minishell
{
	char						*cmd_line;
	char						*cwd;
	char						**tokens;
	char						**env;
	t_command_node				*pipeline;
	size_t						cmd_count;
	int							**pipes;
	int							**here_doc_pipes;

}								t_minishell;

typedef struct s_command_node
{
	t_command_node				*next;
}								t_command_node;

/* COLORS */
# define GREEN				"\033[0;92m"
# define RED				"\033[0;91m"
# define DEF_COLOR 			"\033[0;39m"

/* STATUS */
# define SUCCESS			0

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE		34
# define SINGLE_QUOTE		39
# define EMPTY				' '
# define LINE_BREAK			'\n'
# define EQUAL				'='

/* BUILT INS (COMMANDS) */
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD			"exit"
# define ECHO_CMD			"echo"
# define CD_CMD				"cd"
# define PWD_CMD			"pwd"
# define EXPORT_CMD			"export"
# define UNSET_CMD			"unset"
# define ENV_CMD			"env"
# define FLAG_N				"-n"

/* ERROR MESSAGES */
# define ERROR_MALLOC		"Malloc Fails\n"

/* PROTOTYPES */	
void							parse_cmd_line(t_minishell *minishell);
void							build_pipeline(t_minishell *minishell);
void							exec_pipeline(t_minishell *minishell);
void							clean_minishell(t_minishell *minishell);
void							exit_minishell(t_minishell *minishell,
									char *msg, int status);

/* BUILT-INS */
void							select_builtint(t_minishell *minishell);
void							export_cmd(t_minishell *minishell);
void							cd_cmd(t_minishell *minishell);
void							unset_cmd(t_minishell *minishell, char **cmd);
int								env_cmd(t_minishell *minishell);
int								pwd_cmd(char **cwd);
int								echo_cmd(char **cmd);

/* INIT */
int								init_env(char **env, t_minishell *minishell);

/* UTILS */
int								get_total_commands(char *cmd_line);
int								get_len_matrix(char **matrix);
int								get_cpy_env(t_minishell *minishell,
									char **matrix_ori);
void							free_matrix(char **mat, int i);

#endif