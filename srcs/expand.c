#include "../include/minishell.h"

char	*handle_non_var(char *var_start, char **buffer, int *double_quoted)
{
	char	*current;
	char	*str;
	char	*join;

	current = var_start;
	while (*current && *current != '$')
	{
		if (*current == '"')
			*double_quoted *= -1;
		if (*current == '\'' && *double_quoted == -1)
			current = ft_strchr(++current, '\'');
		current++;
	}
	str = substring(var_start, current);
	if (!str)
		return (NULL);
	join = ft_strjoin(*buffer, str);
	free(str);
	if (!join)
		return (NULL);
	free(*buffer);
	*buffer = join;
	return (current);
}

char	*find_var_end(char *var_start)
{
	char	*var_end;

	var_end = var_start;
	if (*var_end == '?')
		var_end++;
	else
	{
		while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
			var_end++;
	}
	return (var_end);
}

char	*get_var_value(char *var_name, t_minishell *minishell)
{
	char	*var_value;

	if (ft_strequals(var_name, "?") || *var_name == '\0')
	{
		if (*var_name == '\0')
			var_value = ft_strdup("$");
		else
			var_value = ft_itoa(minishell->last_exit_code);
		if (!var_value)
		{
			printf("%s\n", MALLOC_ERR_MSG);
			free(var_name);
			return (NULL);
		}
		return (var_value);
	}
	var_value = get_value_var_env(minishell->envp, var_name);
	if (!var_value)
		var_value = "";
	return (ft_strdup(var_value));
}

char	*handle_var(char *var_start, char **buffer, t_minishell *minishell)
{
	char	*var_name;
	char	*var_value;
	char	*var_end;
	char	*join;

	var_end = find_var_end(var_start);
	var_name = substring(var_start, var_end);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name, minishell);
	free(var_name);
	if (!var_value)
		return (NULL);
	join = ft_strjoin(*buffer, var_value);
	free(var_value);
	if (!join)
		return (NULL);
	free(*buffer);
	*buffer = join;
	return (var_end);
}

char	*expand_token(char *token, t_minishell *minishell)
{
	char	*buffer;
	int		double_quoted;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	double_quoted = -1;
	while (*token)
	{
		if (*token == '$')
			token = handle_var(++token, &buffer, minishell);
		else
			token = handle_non_var(token, &buffer, &double_quoted);
		if (!token)
		{
			free(buffer);
			return (NULL);
		}
	}
	remove_quotes(buffer);
	return (buffer);
}
