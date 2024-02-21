/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:26:59 by brayan            #+#    #+#             */
/*   Updated: 2024/02/21 14:24:14 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: env != NULL
* POST: Devuelve la longitud del env
*/
int	get_len_env(t_env *env)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

/*
* PRE: env != NULL
* POST: Imprime por consola las variables de entorno del minishell
*		segun el modo (MODE_ENV, MODE_EXPORT)
*/
void	print_env(t_env *env, char mode)
{
	t_env	*tmp;
	int		i;

	i = -1;
	tmp = env;
	while (tmp)
	{
		if (mode == MODE_EXPORT)
			printf("declare -x ");
		if (mode == MODE_EXPORT || mode == MODE_ENV)
			printf("%s = %s", tmp->key, tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

/*
* PRE: -
* POST: Devolvera la variable del env que tenga el
*		content == key || content == value segun el parametro
*		de busqueda que corresponda, en caso de que no la encuentre, 
*		devolvera NULL
*/
t_env	*get_var_env(t_env *env, char *content)
{
	int		len_content;
	t_env	*tmp;

	if (!env || !content)
		return (NULL);
	tmp = env;
	len_content = ft_strlen(content);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, content) == 0
			|| ft_strcmp(tmp->value, content) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
* PRE: -
* POST: Libera la memoria de la lista
*/
void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current)
	{
		next = current->next;
		if (current)
		{
			if (current->value)
				free(current->value);
			if (current->key)
				free(current->key);
			free(current);
		}
		current = next;
	}
	*env = NULL;
}
