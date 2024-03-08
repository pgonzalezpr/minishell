#include "../include/minishell.h"

void	print_str_list(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		printf("         ");
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

void	print_cmd(t_command *cmd)
{
	t_list			*curr;
	t_redirection	*redir;

	printf("Command index: %d\n", cmd->index);
	printf("Args: \n");
	print_str_list(cmd->args);
	printf("Redirections: \n");
	curr = cmd->redirections;
	while (curr)
	{
		redir = curr->content;
		printf("         ");
		printf("Redir code: %d, Name: %s\n", redir->code, redir->name);
		curr = curr->next;
	}
}

void	print_minishell(t_minishell *minishell)
{
	t_list	*curr;

	printf("Tokens: \n");
	print_str_list(minishell->tokens);
	printf("Cmd count: %d\n", minishell->cmd_count);
	curr = minishell->commands;
	while (curr)
	{
		print_cmd(curr->content);
		curr = curr->next;
	}
}

/*
* PRE: -
* POST: Imprime las variables de entorno que controla CD. (SOLO PARA DEBUGGEAR).
*/
void	print_vars_cd(char **env, char *cwd)
{
	printf("ANTES OLDPWD: %s\n", get_value_var_env(env, VAR_OLDPWD));
	printf("ANTES PWD: %s\n", get_value_var_env(env, VAR_PWD));
	printf("ANTES HOME: %s\n", get_value_var_env(env, VAR_HOME));
	printf("ANTES MINISHEL CWD: %s\n", cwd);
	printf("-------------------------------------------\n");
}
