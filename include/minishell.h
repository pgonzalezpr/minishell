/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:26:14 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 22:21:05 by brayan           ###   ########.fr       */
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

}								t_minishell;

/* COLORS */
# define GREEN						"\033[0;92m"
# define RED						"\033[0;91m"
# define DEF_COLOR 					"\033[0;39m"

/* STATUS */
# define SUCCESS					0
# define POS_NOT_FOUNDED			-4

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE				34
# define SINGLE_QUOTE				39
# define NULL_STR					'\0'
# define EMPTY						' '
# define LINE_BREAK					'\n'
# define EQUAL						'='
# define DOLLAR_SIGN				'$'
# define BACK_CD					".."
# define FOWARD_SLAH				47

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
# define VAR_OLDPWD					"OLDPWD"
# define VAR_PWD					"PWD"
# define VAR_OLDPWD_WITH_EQUAL		"OLDPWD="
# define VAR_PWD_WITH_EQUAL			"PWD="
# define FLAG_N						"-n"

/* ERROR MESSAGES */
# define ERROR_MALLOC				"Malloc Fails\n"
# define MSG_CD_MISSING_ARGS		"cd: missing argument\n"
# define MSG_CD_FAILS				"cd fails!\n"
# define MSG_MORE_THAN_TWO_ARGS_CD 	"cd: more than two args\n"
# define MSG_MORE_THAN_TWO_ARGS_ENV "env: more than two args\n"
# define MSG_GET_CWD				"cd: get_cwd fails\n"

/* PROTOTYPES */
void							build_pipeline(t_minishell *minishell);
void							exec_pipeline(t_minishell *minishell);
void							clean_minishell(t_minishell *minishell);
void							exit_minishell(t_minishell *minishell,
									char *msg, int status);
void							free_tokens(t_token_node *tokens);
void							free_pipeline(t_command_node *pipeline);
void							free_pipe_arr(int **arr, size_t size);
void							tokenize_cmd_line(t_minishell *minishell);
void							remove_quotes(t_token_node *token_node);
void							replace_env_vars(t_token_node *token_node,
									t_minishell *minishell);

/* BUILT-INS */
void							select_builtin(t_minishell *minishell);
void							builtin_export(t_minishell *minishell);
void							builtin_cd(t_minishell *minishell, char **cmd);
void							builtin_unset(t_minishell *minishell,
									char **cmd);
int								builtin_env(t_minishell *minishell);
int								builtin_pwd(char **cwd);
int								builtin_echo(char **cmd, char **env);
void 							update_vars_path_and_old_path(t_minishell *minishell,
								char *old_path, char *new_path);

/* INIT */
int								init_env(char **env, t_minishell *minishell);

/* UTILS */
int								get_total_commands(char *cmd_line);
int								get_len_matrix(char **matrix);
void							free_matrix(char **mat, int i);

/* UTILS_ENV */
int								are_equal_variables(char *variable_1,
									char *variable_2);
int								get_len_variable(char *variable);
int								get_pos_var_env(char **env,
									char *searched_var);
int								get_ncpy_env(t_minishell *minishell,
									char **matrix_ori, int size);

#endif