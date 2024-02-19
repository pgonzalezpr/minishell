#include "../include/minishell.h"

char	*substring(char *start, char *end)
{
	char	*str;

	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, start, end - start + 1);
	return (str);
}

int	ft_strequals(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
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
