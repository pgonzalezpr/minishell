#include "../include/minishell.h"

void	replace_env_vars(t_token_node *token_node, t_minishell *minishell)
{
	/*char	*token;
	size_t	offset;
	size_t	begin;
	char	*env_var_name;

	token = token_node->token;
	offset = 0;
	while (token[offset])
	{
		if (token[offset] == '\'')
		{
			while (token[offset] != '\'')
				offset++;
		}
		if (token[offset] == '$')
			env_var_name = extract_var_name(&token[offset]);
		offset++;
	}
	*/
	if (token_node && minishell)
		return ;
}

void	remove_quotes(t_token_node *token_node)
{
	char	*token;
	size_t	offset;
	char	quote;

	token = token_node->token;
	offset = 0;
	while (token[offset])
	{
		if (token[offset] == '"' || token[offset] == '\'')
		{
			quote = token[offset];
			ft_memmove(&token[offset], &token[offset + 1],
				ft_strlen(&token[offset + 1]) + 1);
			while (token[offset] != quote)
				offset++;
			ft_memmove(&token[offset], &token[offset + 1],
				ft_strlen(&token[offset + 1]) + 1);
		}
		else
			offset++;
	}
}
