/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:52:30 by brayan            #+#    #+#             */
/*   Updated: 2024/02/13 01:19:13 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Imprimira el valor de la variable de entorno por consola,
*		Si la misma existe
*/
static void	print_dollar_case(char **cmd, char **env, int i, int j)
{
	int		pos_var_env;
	char	*aux_var;

	if (cmd[i][j] == DOLLAR_SIGN)
	{
		aux_var = cmd[i];
		aux_var++;
		if (cmd[i][j + 1] == NULL_STR)
			printf("%c", DOLLAR_SIGN);
		else
		{
			pos_var_env = get_pos_var_env(env, aux_var);
			if (pos_var_env != POS_NOT_FOUNDED)
			{
				aux_var = ft_strchr(env[pos_var_env], EQUAL);
				printf("%s", ++aux_var);
			}
			else if (ft_isdigit(*aux_var) && aux_var + 1)
			{
				aux_var++;
				printf("%s", aux_var);
			}
		}
	}
}

/*
* PRE: -
* POST: Imprimira un caracter por consola.
*/
static void	print_case(char **cmd, char **env, int i)
{
	int		j;

	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != DOUBLE_QUOTE && cmd[i][j] != SINGLE_QUOTE \
				&& cmd[i][j] != DOLLAR_SIGN)
				printf("%c", cmd[i][j]);
			else if (cmd[i][j] == DOLLAR_SIGN)
			{
				print_dollar_case(cmd, env, i, j);
				break ;
			}
		}
		if (cmd[i + 1])
			printf("%c", EMPTY);
	}
}

/*
* PRE: cmd != NULL && env != NULL
* POST: Mostrara un mensaje por el standar output.
*/
int	echo_cmd(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		printf("%c", LINE_BREAK);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd[1], FLAG_N, 2) == 0)
		i = 1;
	print_case(cmd, env, i);
	if (ft_strncmp(cmd[1], FLAG_N, 2) != 0)
		printf("%c", LINE_BREAK);
	return (SUCCESS);
}
