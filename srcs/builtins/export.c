/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/15 00:26:40 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * PRE: minishell != NULL && cmd != NULL
 * POST:
 */
static int get_len_env_without_repeats(t_minishell *minishell, char **cmd)
{
	char *var_name_env;
	char *var_name_cmd;
	int len_new_env;
	int i;
	int j;

	len_new_env = get_len_matrix(minishell->env) + get_total_commands(cmd);
	i = 0;
	while (cmd[++i])
	{
		/*
		-> export, PATH="abc", NUEVA="VALOR1" VAR= OTRA
		-> la encuentro y solo tengo que sobreescribirla (bajo 1 la long total)
		-> es una nueva variable (la ignoro)
		*/
		j = -1;
		var_name_cmd = ft_strrchr(cmd[i], EQUAL);
		if (var_name_cmd)
		{
			var_name_cmd++;
			while (minishell->env[++j])
			{
				var_name_env = ft_strrchr(minishell->env[j], EQUAL);
				var_name_env++;
				if (are_equal_variables(var_name_cmd, var_name_env))
				{
					len_new_env--;
					break;
				}
			}
		}
	}
	return (len_new_env);
}

/*
 * PRE: minishell != NULL && cmd != NULL
 * POST:
 */
void builtin_export(t_minishell *minishell, char **cmd)
{
	char *new_env;
	int len_env;

	len_env = get_len_env_without_repeats(minishell, cmd);
	new_env = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!new_env)
	{
		// CONTROLAR FALLO MEMORIA
	}
	/*
	-> Ya pido la memoria para el nuevo env
	-> Copiar las que no sufriran cambios, las que no estan en cmd
	-> Agregar las nuevas en los casos 
		(OTRA, VAR_NUEVA="valor", VAR_NUEVA=)
	-> Sobreescribir las variables viejas de env con los valores nuevos
		(PATH="nuevo_valor", PATH=)
	-> Liberar el env viejo
	-> apuntar el minishel->env = new_env;
	*/
	new_env[len_env] = NULL;
}
