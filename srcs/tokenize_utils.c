#include "../include/minishell.h"

char	*substring(char *start, char *end)
{
	char	*str;

	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", MALLOC_ERR_MSG);
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

int	is_metachar(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	get_operator_len(char *start)
{
	if (ft_strncmp(start, ">>", 2) == 0 || ft_strncmp(start, "<<", 2) == 0)
		return (2);
	return (1);
}
