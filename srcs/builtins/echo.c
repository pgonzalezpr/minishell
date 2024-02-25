/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:52:30 by brayan            #+#    #+#             */
/*   Updated: 2024/02/25 23:54:42 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Devuelve la longitud de var filtrado
*		es decir, sin contar los simbolos $ " '
*/
static int	get_len_filtered_var(const char	*var)
{
	int	len;

	len = 0;
	while (*var)
	{
		if (*var != DOUBLE_QUOTE && *var != DOLLAR_SIGN \
		&& *var != SINGLE_QUOTE)
			len++;
		var++;
	}
	return (len);
}

/*
* PRE: -
* POST: Devolvera la cantidad de caracteres filtrados de var,
*		Ademas modificara el parametro filter_var, dejandolo con el 
*		contenido de var filtrado.
*/
static char	*get_filter_key(const char *key_var, int *total_simbols_filtered)
{
	int		i;
	int		j;
	int		len_var_filtered;
	char	*filter_var;

	if (!key_var)
		return (NULL);
	len_var_filtered = get_len_filtered_var(key_var);
	filter_var = (char *)malloc(len_var_filtered + 1);
	if (!filter_var)
		return (perror(RED ERROR_MALLOC DEF_COLOR), NULL);
	i = 0;
	j = -1;
	while (key_var[++j])
	{
		if (key_var[j] != DOUBLE_QUOTE && key_var[j] != DOLLAR_SIGN \
		&& key_var[j] != SINGLE_QUOTE)
			filter_var[i++] = key_var[j];
	}
	filter_var[i++] = NULL_STR;
	(*total_simbols_filtered) = ft_strlen(key_var) - len_var_filtered;
	return (filter_var);
}

/*
* PRE: -
* POST: Imprimira el valor de la variable de entorno por consola,
*		Si la misma existe
*/
static int	print_dollar_case(char **cmd, t_env *env, int i, int j)
{
	t_env	*node;
	int		total_simbols_filtered;
	char	*searched_name;

	searched_name = get_filter_key(cmd[i], &total_simbols_filtered);
	if (!searched_name)
		return (ERROR);
	if (cmd[i][j + 1] == NULL_STR)
		printf("%c", DOLLAR_SIGN);
	else if (ft_strlen(cmd[i]) > 0 && ((cmd[i][0] == DOUBLE_QUOTE && \
		cmd[i][ft_strlen(cmd[i]) - 1] == DOUBLE_QUOTE) || \
		(cmd[i][0] == DOLLAR_SIGN && total_simbols_filtered == 1)))
	{
		node = get_var_env(env, searched_name);
		if (node)
			printf("%s", node->value);
	}
	free(searched_name);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Imprimira un caracter por la terminal, 
*		devolviendo el estado de la operacion.
*/	
static int	print_case(char **cmd, t_env *env, int i)
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
				if (print_dollar_case(cmd, env, i, j) == ERROR)
					return (ERROR);
				break ;
			}
		}
		if (cmd[i + 1])
			printf("%c", EMPTY);
	}
	return (SUCCESS);
}

/*
* PRE: cmd != NULL && env != NULL
* POST: Mostrara un mensaje por el standar output, y devolvera
*		el estado de la operacion (SUCCESS o ERROR)
*/
int	builtin_echo(t_env *env, char **cmd)
{
	int	i;
	int	status;

	i = 0;
	status = SUCCESS;
	if (!cmd[1])
	{
		printf("%c", LINE_BREAK);
		return (status);
	}
	else if (ft_strncmp(cmd[1], FLAG_N, 2) == 0)
		i = 1;
	status = print_case(cmd, env, i);
	if (ft_strncmp(cmd[1], FLAG_N, 2) != 0)
		printf("%c", LINE_BREAK);
	return (status);
}
