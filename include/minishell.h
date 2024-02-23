/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:26:14 by brayan            #+#    #+#             */
/*   Updated: 2024/02/23 01:44:19 by brayan           ###   ########.fr       */
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
typedef struct s_env			t_env;

typedef struct s_command_node
{
	t_command_node				*next;
}								t_command_node;

typedef struct s_token_node
{
	char						*token;
	t_token_node				*next;
}								t_token_node;

typedef struct s_env
{
	char						*key;
	char						*value;
	t_env						*next;
}								t_env;

typedef struct s_minishell
{
	char						*cmd_line;
	char						*cwd;
	t_env						*env;
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
# define ERROR						-1
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
# define FOWARD_SLAH_STR			"/"
# define FOWARD_SLAH				47

/* BUILT INS (COMMANDS) */
# define EXIT_COMMAND_NOT_FOUND 	127
# define EXIT_CMD					"exit"
# define EXIT_CMD_2 				"'exit'"
# define EXIT_CMD_3					"\"exit\""
# define ECHO_CMD					"echo"
# define ECHO_CMD_2					"'echo'"
# define ECHO_CMD_3					"\"echo\""
# define CD_CMD						"cd"
# define CD_CMD_2					"'cd'"
# define CD_CMD_3					"\"cd\""
# define PWD_CMD					"pwd"
# define PWD_CMD_2					"'pwd'"
# define PWD_CMD_3					"\"pwd\""
# define EXP_CMD					"export"
# define EXP_CMD_2 					"'export'"
# define EXP_CMD_3					"\"export\""
# define UNSET_CMD					"unset"
# define UNSET_CMD_2 				"'unset'"
# define UNSET_CMD_3				"\"unset\""
# define ENV_CMD					"env"
# define ENV_CMD_2 					"'env'"
# define ENV_CMD_3					"\"env\""
# define VAR_OLDPWD					"OLDPWD"
# define VAR_PWD					"PWD"
# define VAR_OLDPWD_WITH_EQUAL		"OLDPWD="
# define VAR_PWD_WITH_EQUAL			"PWD="
# define FLAG_N						"-n"
# define MODE_EXPORT				'X'
# define MODE_ENV					'E'
# define MAX_PATH					4200

/* ERROR MESSAGES */
# define ERROR_MALLOC				"Malloc Fails\n"
# define MSG_CD_MISSING_ARGS		"cd: missing argument\n"
# define MSG_CD_FAILS				"cd fails!\n"
# define MSG_MORE_THAN_TWO_ARGS_CD 	"cd: more than two args\n"
# define MSG_MORE_THAN_TWO_ARGS_ENV "env: more than two args\n"
# define MSG_GET_CWD				"cd: get_cwd fails\n"
# define MSG_COMMAND_NOT_FOUND		": command not found\n"

/* PROTOTYPES */
void	build_pipeline(t_minishell *minishell);
void	exec_pipeline(t_minishell *minishell);
void	clean_minishell(t_minishell *minishell);
void	exit_minishell(t_minishell *minishell, char *msg, int status);
void	free_tokens(t_token_node *tokens);
void	free_pipeline(t_command_node *pipeline);
void	free_pipe_arr(int **arr, size_t size);
void	tokenize_cmd_line(t_minishell *minishell);
void	remove_quotes(t_token_node *token_node);
void	replace_env_vars(t_token_node *token_node, t_minishell *minishell);

/* BUILT-INS */
int		select_builtin(t_minishell *minishell);

/* PWD.C */
int		builtin_pwd(char **cwd);

/* EXPORT.C */
int		builtin_export(t_minishell *minishell, char **cmd);

/* UNSET.C */
int		builtin_unset(t_minishell *minishell, char **cmd);

/* CD.C */
int		builtin_cd(t_minishell *minishell, char **cmd);

/* ENV.C */
int		builtin_env(t_minishell *minishell);

/* CD_UTILS.C*/
int		update_cd_vars(t_minishell *minishell);

/* ECHO.C */
int		builtin_echo(t_env *env, char **cmd);

/* INIT.C */
int		init_env(t_minishell *minishell, char **env);

/* UTILS.C */ 
int		get_total_commands(char *cmd_line);
int		get_len_matrix(char **matrix);
int		ft_strcmp(char *s1, char  *s2);
void	free_matrix(char **mat, int i);

/* UTILS_ENV.C */
void	print_env(t_env *env, char mode);
void	free_env(t_env *env);
t_env	*get_var_env(t_env *env, char *content);
int		get_len_env(t_env *env);
t_env	*get_new_node_env(char *key, char *value);

/* UTILS_ENV 2.C */
t_env	*get_last_node_env(t_env *env);
void	add_back_to_env(t_env **env, t_env *new);
int		set_node_content(char *content, t_env **node);
int		get_len_key_var(char *key);
int		del_node_env(t_env *env, t_env *node);

#endif