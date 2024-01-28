#include "../include/minishell.h"

void	print_token(char *begin, char *end)
{
	if (begin == end)
		return ;
	write(STDOUT_FILENO, begin, (size_t)(end - begin));
	write(STDOUT_FILENO, "\n", 1);
}

void	tokenize(char *cmdLine)
{
	char	*begin;
	char	quote;

	while (*cmdLine)
	{
		while (*cmdLine == ' ')
			cmdLine++;
		begin = cmdLine;
		while (*cmdLine && *cmdLine != ' ' && *cmdLine != '|')
		{
			if (*cmdLine == '"' || *cmdLine == '\'')
			{
				quote = *cmdLine++;
				while (*cmdLine && *cmdLine != quote)
					cmdLine++;
				if (!*cmdLine)
				{
					printf("Error. Unclosed quote\n");
					return ;
				}
			}
			cmdLine++;
		}
		print_token(begin, cmdLine);
		if (!*cmdLine)
			break ;
		if (*cmdLine == '|')
		{
			begin = cmdLine;
			cmdLine++;
			print_token(begin, cmdLine);
		}
	}
}

void	parse_cmd_line(t_minishell *minishell)
{
	tokenize(minishell->cmd_line);
}
