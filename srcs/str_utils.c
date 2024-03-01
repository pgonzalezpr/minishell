#include "../include/minishell.h"

char	*substring(char *start, char *end)
{
	char	*str;

	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
	{
		printf("%s\n", MALLOC_ERR_MSG);
		return (NULL);
	}
	ft_strlcpy(str, start, end - start + 1);
	return (str);
}

int	ft_strequals(char *s1, char *s2)
{
	return ((ft_strlen(s1) == ft_strlen(s2)) && ft_strncmp(s1, s2,
			ft_strlen(s1)) == 0);
}

int	is_redirection(char *str)
{
	return (ft_strequals(str, IN_RED) || ft_strequals(str, OUT_RED)
		|| ft_strequals(str, HERE_DOC) || ft_strequals(str, OUT_RED_APP));
}

int	is_operator(char *str)
{
	return (ft_strequals(str, PIPE) || is_redirection(str));
}

void	remove_quotes(char *token)
{
	int		offset;
	char	quote;

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
