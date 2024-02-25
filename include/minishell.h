/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:26:14 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 04:49:06 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char						*cwd;
	char						**env;
	t_token_node				*tokens;
	t_command_node				*pipeline;
	size_t						cmd_count;
	int							**pipes;
	int							**here_doc_pipes;
	int							last_exit_code;

}								t_minishell;

/* COLORS */
# define GREEN				"\033[0;92m"
# define RED				"\033[0;91m"
# define DEF_COLOR 			"\033[0;39m"

/* STATUS */
# define SUCCESS			0
# define POS_NOT_FOUNDED	-4
# define EXIT_CMD_NOT_FOUND         127

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE		34
# define SINGLE_QUOTE		39
# define NULL_STR			'\0'
# define EMPTY				' '
# define LINE_BREAK			'\n'
# define EQUAL				'='
# define DOLLAR_SIGN		'$'
# define BACK_CD			".."
# define FOWARD_SLAH		47

/* BUILT INS (COMMANDS) */
# define EXIT_COMMAND_NOT_FOUND 	127
# define EXIT_BUILTIN				"exit"
# define EXIT_BUILTIN_2 			"'exit'"
# define EXIT_BUILTIN_3				"\"exit\""
# define ECHO_BUILTIN				"echo"
# define ECHO_BUILTIN_2 			"'echo'"
# define ECHO_BUILTIN_3				"\"echo\""
# define CD_BUILTIN					"cd"
# define CD_BUILTIN_2 				"'cd'"
# define CD_BUILTIN_3				"\"cd\""
# define PWD_BUILTIN				"pwd"
# define PWD_BUILTIN_2 				"'pwd'"
# define PWD_BUILTIN_3				"\"pwd\""
# define EXP_BUILTIN				"export"
# define EXP_BUILTIN_2 				"'export'"
# define EXP_BUILTIN_3				"\"export\""
# define UNSET_BUILTIN				"unset"
# define UNSET_BUILTIN_2 			"'unset'"
# define UNSET_BUILTIN_3			"\"unset\""
# define ENV_BUILTIN				"env"
# define ENV_BUILTIN_2 				"'env'"
# define ENV_BUILTIN_3				"\"env\""
# define FLAG_N						"-n"

/* ERROR MESSAGES */
# define ERROR_MALLOC				"Malloc Fails\n"
# define MSG_CD_MISSING_ARGS		"cd: missing argument\n"
# define MSG_CD_FAILS				"cd fails!\n"
# define MSG_MORE_THAN_TWO_ARGS_CD 	"cd more than two args\n"
# define MSG_GET_CWD				"cd: get_cwd fails\n"
# define MALLOC_ERR_MSG             "Allocation error\n"
# define UNCLOSED_QUOTE_MSG         "Error. Unclosed quote"

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
void							select_builtin(t_minishell *minishell);
void							builtin_export(t_minishell *minishell);
void							builtin_cd(t_minishell *minishell, char **cmd);
void							builtin_unset(t_minishell *minishell,
									char **cmd);
int								builtin_env(t_minishell *minishell);
int								builtin_pwd(char **cwd);
int								builtin_echo(char **cmd, char **env);

/* INIT */
int								init_env(char **env, t_minishell *minishell);

/* UTILS */
int								get_total_commands(char *cmd_line);
int								get_len_matrix(char **matrix);
void							free_matrix(char **mat, int i);

/* UTILS_ENV */
int								get_cpy_env(t_minishell *minishell,
									char **matrix_ori);
int								are_equal_variables(char *variable_1,
									char *variable_2);
int								get_len_variable(char *variable);
int								get_pos_var_env(char **env,
									char *searched_var);

#endif