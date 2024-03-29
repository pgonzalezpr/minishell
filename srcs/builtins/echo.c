/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:52:30 by brayan            #+#    #+#             */
/*   Updated: 2024/03/29 16:18:04 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Imprimira un caracter por la terminal, 
*		devolviendo el estado de la operacion.
*/
static int	is_valid_flag_n(char *flag)
{
	if (!flag || (flag && flag[0] == FLAG_SYMBOL && !flag[1])
		|| (flag && flag[0] == '0' && !flag[1]))
		return (0);
	flag++;
	while (*flag && *flag == FLAG_N)
		flag++;
	return (*flag == NULL_STR);
}

/*
* PRE: -
* POST: Imprimira un caracter por la terminal, 
*		devolviendo el estado de la operacion.
*/	
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

/*
* PRE: cmd != NULL && env != NULL
* POST: Mostrara un mensaje por el standar output, y devolvera
*		el estado de la operacion (SUCCESS o ERROR)
*/
int	builtin_echo(char **env, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		printf("%c", LINE_BREAK);
	else if (is_valid_flag_n(cmd[1]))
		i = 1;
	print_cmd(cmd, env, i);
	if (i != 1)
		printf("%c", LINE_BREAK);
	return (SUCCESS);
}
