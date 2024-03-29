/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:26:14 by brayan            #+#    #+#             */
/*   Updated: 2024/03/23 20:01:26 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include "../include/readline/history.h"
# include "../include/readline/readline.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* GLOBAL VARIABLE */
extern int	g_exit_status;

/* STRUCTS */
typedef struct s_command
{
	t_list	*args;
	t_list	*redirections;
	int		index;
}			t_command;

typedef struct s_redirection
{
	int		code;
	char	*name;
}			t_redirection;

typedef struct s_minishell
{
	char	*cmd_line;
	char	**envp;
	t_list	*tokens;
	t_list	*commands;
	int		cmd_count;
	int		last_exit_code;
	int		**pipes;
	int		**hd_pipes;
}			t_minishell;

# define MAX 4200

/* COLORS */
# define GREEN "\033[0;92m"
# define RED "\033[0;91m"
# define DEF_COLOR "\033[0;39m"

/* STATUS */
# define POS_NOT_FOUNDED -4
# define INVALID_KEY -5
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_ERROR 2
# define SUCCESS 1
# define ERROR -1
# define POS_NOT_FOUNDED -4
# define IGNORE -15
# define CLEAN_ENV -10
# define NOT_CLEAN_ENV -11
# define EXIT_CHILD_WAS_INTERRUPTED_BY_SIGQUIT 131
# define EXIT_CHILD_WAS_INTERRUPTED_BY_SIGINT 130

/* REDIRECTIONS CODES */
# define IN_RED_CODE 1
# define OUT_RED_CODE 2
# define HERE_DOC_CODE 3
# define OUT_RED_APP_CODE 4

/* SPECIAL SYMBOLS */
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39
# define NULL_STR '\0'
# define PIPE "|"
# define IN_RED "<"
# define OUT_RED ">"
# define HERE_DOC "<<"
# define OUT_RED_APP ">>"
# define EMPTY ' '
# define LINE_BREAK '\n'
# define EQUAL '='
# define DOLLAR_SIGN '$'
# define UNDERSCORE '_'
# define CURRENT_DIRECTORY '.'
# define BACK_CD ".."
# define FORWARD_SLAH_ST "/"
# define FORWARD_SLAH 47

/* BUILT INS (COMMANDS) */
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_CMD "exit"
# define ECHO_CMD "echo"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define EXP_CMD "export"
# define UNSET_CMD "unset"
# define ENV_CMD "env"
# define VAR_OLDPWD "OLDPWD"
# define VAR_PWD "PWD"
# define VAR_HOME "HOME"
# define MSG_DECLARE "declare -x "
# define VAR_PATH_WITH_EQUAL "PATH="
# define FLAG_N 'n'
# define FLAG_SYMBOL '-'
# define MODE_EXPORT 'X'
# define MODE_ENV 'E'
# define MODE_INTERACTIVE -1
# define MODE_NO_INTERACTIVE -2
# define MINISHELL_PATH "./minishell"

/* ERROR MESSAGES */
# define MSG_SIGNAL_ERROR "Signal fails\n"
# define MSG_TOO_MANY_ARGS_EXIT "minishell: exit: too many arguments\n"
# define MSG_TOO_MANY_ARGS_ENV "minishell: env: too many arguments\n"
# define MSG_TOO_MANY_ARGS_PWD "minishell: pwd: too many arguments\n"
# define MSG_TOO_MANY_ARGS_MINI "minishell: too many arguments\n"
# define MSG_HOME_UNSET "minishell: cd: HOME not set\n"
# define MSG_CD_NO_SUCH_FILE "minishell: cd: No such file or directory\n"
# define MSG_CD_PERMISSION_DENIED "minishell: cd: Permission denied\n"
# define MSG_TOO_MANY_ARGS_CD "minishell: cd: too many arguments\n"
# define MSG_GET_CWD "minishell: cd: getcwd fails\n"
# define MSG_COMMAND_NOT_FOUND ": command not found\n"
# define MSG_EXIT "exit\n"
# define ERROR_MALLOC "Malloc Fails\n"
# define SYNTAX_ERR_MSG "Syntax Error\n"
# define MALLOC_ERR_MSG "Allocation error\n"
# define UNCLOSED_QUOTE_MSG "Error. Unclosed quote\n"
# define FORK_ERR_MSG "Fork error\n"
# define REDIR_ERR_MSG "Redirection error\n"
# define EXEC_ERR_MSG "Execve error\n"
# define PROMPT_ERR_MSG "Error builing prompt\n"
# define MSG_ERROR_SIGNAL "Error configuring signal\n"
# define MSG_ERROR_CPY_ENV "Error get_cpy_env fails\n"

/* PROTOTYPES */
int			tokenize_cmdline(t_minishell *minishell);
int			process_tokens(t_minishell *minishell);
void		remove_quotes(char *token);
int			check_syntax(t_minishell *minishell);
char		*substring(char *start, char *end);
int			ft_strequals(char *s1, char *s2);
int			is_redirection(char *str);
int			is_operator(char *str);
int			is_metachar(char c);
int			get_operator_len(char *start);
char		*expand_token(char *token, t_minishell *minishell);
int			build_pipeline(t_minishell *minishell);
int			check_builtin(t_minishell *minishell);
int apply_redirections(t_list *redirs, int index,
                       t_minishell *minishell);
void		print_minishell(t_minishell *minishell);
int			init_pipes(t_minishell *minishell);
char		**build_str_arr_from_lst(t_list *lst);
void		free_str_arr(char **arr);
void		close_pipes(t_minishell *minishell);
void		free_pipe_arr(int **arr, size_t size);
int			exec_pipeline(t_minishell *minishell);
char		*build_cmd_path(char *cmd_name, t_minishell *minishell);
void		clean_minishell(t_minishell *minishell, int exit_mode);
void		del_str(char *str);
int			is_numeric(char *str);
void		exit_minishell(t_minishell *minishell, char *msg, int status);
int			is_builtin(char *name);
void		exec_builtin(t_command *cmd, char **argv, t_minishell *minishell,
				int exit_process);
int			builtin_pwd(int total_commands);
int			builtin_export(t_minishell *minishell, char **cmd);
int			builtin_unset(t_minishell *minishell, char **cmd);
int			builtin_cd(t_minishell *minishell, char **cmd);
int			builtin_env(t_minishell *minishell);
int			builtin_echo(char **env, char **cmd);
int			builtin_exit(t_minishell *minishell, char **args);
int			get_cpy_env(char ***env_cpy, char **env_original, int total_cpy,
				int pos_not_copy);
int			get_len_env(char **env);
void		free_env(char **env, int size);
char		*get_value_var_env(char **env, char *key);
void		print_env(char **env, char mode);
int			get_len_key_var(char *key);
char		*get_new_var(char *key, char *value);
int			get_pos_var_env(char **env, char *key);
char		*build_prompt(t_minishell *minishell);
int			is_valid_key_format(char *key);
void		remove_foward_slash(char path[MAX]);
int			check_access_to_path(char *path);
int			update_cd_vars(char ***env, char *new_value_pwd);

// LA USO PARA DEBUGGEAR Y VER QUE LAS VARS DE CD SE ACTUALIZAN.
void		print_vars_cd(char **env, char *cwd);

//	MANEJO DE SIGNALS
int			init_signal(int nb_signal, void (*handler)(int));
int			exec_signals(int mode);
void		handle_exit_status(int *last_exit_code, int status);

#endif
