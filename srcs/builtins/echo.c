/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:52:30 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:44:05 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_flag_n(char *flag)
{
	if (!flag || (flag && flag[0] == FLAG_SYMBOL && !flag[1])
		|| (flag && flag[0] == '0' && !flag[1]) \
		|| (flag && flag[0] != FLAG_SYMBOL))
		return (0);
	flag++;
	while (*flag && *flag == FLAG_N)
		flag++;
	return (*flag == NULL_STR);
}

static void	print_cmd(char **cmd, char **env, int i)
{
	char	*key;
	char	*value;
	int		j;

	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == DOLLAR_SIGN && cmd[i][j + 1])
			{
				key = &cmd[i][j + 1];
				value = get_value_var_env(env, key);
				if (value)
					printf("%s", value);
				else
					printf("%s", cmd[i] + 1);
				break ;
			}
			else
				printf("%c", cmd[i][j]);
		}
		if (cmd[i + 1])
			printf("%c", EMPTY);
	}
}

int	builtin_echo(char **env, char **cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (!cmd[1])
		printf("%c", LINE_BREAK);
	while (is_valid_flag_n(cmd[i]) && cmd[i])
	{
		flag = 1;
		i++;
	}
	print_cmd(cmd, env, i - 1);
	if (!flag)
		printf("%c", LINE_BREAK);
	return (SUCCESS);
}
