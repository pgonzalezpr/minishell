#include "../include/minishell.h"

int	add_arg(char *arg, t_list **args_lst)
{
	t_list	*new;
	char	*content;

	content = ft_strdup(arg);
	if (!content)
		return (-1);
	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (-1);
	}
	ft_lstadd_back(args_lst, new);
	return (1);
}

int	add_redir(char *redir_symbol, char *name, t_list **redir_lst)
{
	t_redirection	*redir;
	t_list			*redir_node;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (-1);
	ft_memset(redir, 0, sizeof(t_redirection));
	if (ft_strequals(redir_symbol, IN_RED))
		redir->code = IN_RED_CODE;
	else if (ft_strequals(redir_symbol, OUT_RED))
		redir->code = OUT_RED_CODE;
	else if (ft_strequals(redir_symbol, HERE_DOC))
		redir->code = HERE_DOC_CODE;
	else if (ft_strequals(redir_symbol, OUT_RED_APP))
		redir->code = OUT_RED_APP_CODE;
	redir->name = ft_strdup(name);
	redir_node = ft_lstnew(redir);
	if (!redir_node)
	{
		free(redir);
		return (-1);
	}
	ft_lstadd_back(redir_lst, redir_node);
	return (1);
}

int	handle_token(t_list *token, t_list *cmd_node)
{
	t_command	*cmd;

	cmd = (t_command *)cmd_node->content;
	if (is_redirection(token->content))
	{
		if (add_redir(token->content, token->next->content,
				&cmd->redirections) == -1)
			return (-1);
		return (0);
	}
	if (add_arg(token->content, &cmd->args) == -1)
		return (-1);
	return (1);
}

t_list	*add_command(t_minishell *minishell, int index)
{
	t_command	*cmd;
	t_list		*cmd_node;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->index = index;
	cmd_node = ft_lstnew(cmd);
	if (!cmd_node)
	{
		free(cmd);
		return (NULL);
	}
	ft_lstadd_back(&minishell->commands, cmd_node);
	minishell->cmd_count++;
	return (cmd_node);
}

int	build_pipeline(t_minishell *minishell)
{
	t_list	*token;
	t_list	*cmd_node;
	int		index;
	int		result;

	token = minishell->tokens;
	index = -1;
	while (token)
	{
		cmd_node = add_command(minishell, ++index);
		if (!cmd_node)
			return (-1);
		while (token && !ft_strequals(token->content, PIPE))
		{
			result = handle_token(token, cmd_node);
			if (result == -1)
				return (-1);
			if (result == 0)
				token = token->next;
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	return (1);
}
