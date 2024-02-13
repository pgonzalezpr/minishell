/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:26:14 by brayan            #+#    #+#             */
/*   Updated: 2024/02/12 23:30:19 by brayan           ###   ########.fr       */
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
# define GREEN				"\033[0;92m"
# define RED				"\033[0;91m"
# define DEF_COLOR 			"\033[0;39m"

/* STATUS */
# define SUCCESS			0
# define POS_NOT_FOUNDED	-4

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE		34
# define SINGLE_QUOTE		39
# define NULL_STR			'\0'
# define EMPTY				' '
# define LINE_BREAK			'\n'
# define EQUAL				'='
# define DOLLAR_SIGN		'$'

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
void							select_builtint(t_minishell *minishell);
void							export_cmd(t_minishell *minishell);
void							cd_cmd(t_minishell *minishell);
void							unset_cmd(t_minishell *minishell, char **cmd);
int								env_cmd(t_minishell *minishell);
int								pwd_cmd(char **cwd);
int								echo_cmd(char **cmd, char **env);

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