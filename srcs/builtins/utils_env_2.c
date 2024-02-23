/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:42 by brayan            #+#    #+#             */
/*   Updated: 2024/02/23 01:44:32 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Devuelve la longitud de la clave del env.
*/
int	get_len_key_var(char *key)
{
	int	len;

	len = 0;
	while (*key && *key != EQUAL)
	{
		len++;
		key++;
	}
	return (len);
}

/*
* PRE: -
* POST:	Devuelve el ultimo node del env.
*/
t_env	*get_last_node_env(t_env *env)
{
	t_env	*current;

	if (!env)
		return (NULL);
	current = env;
	while (current->next)
		current = current->next;
	return (current);
}

/*
* PRE: -
* POST: Agrega el nuevo nodo al env.
*/
void	add_back_to_env(t_env **env, t_env *new)
{
	t_env	*current;

	if (!env)
		return ;
	current = *env;
	if (!current)
		*env = new;
	else
	{
		current = get_last_node_env(current);
		current->next = new;
	}
}

/*
* PRE: -
* POST: Elimina el node del env que tenga la misma key,
*		retornando el estado de la operacion.
*/
int	del_node_env(t_env *env, t_env *node)
{
	t_env	*current;

	if (!env || !node)
		return (ERROR);
	current = env;
	while (current->next && ft_strcmp(current->next->key, node->key) != 0)
		current = current->next;
	if (!current->next)
		return (ERROR);
	current->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Agrega el new_content al node, cambiando su valor
*		y clave por dicho contenido.
*/
int	set_node_content(char *content, t_env **node)
{
	int		len_key;
	int		len_value;	

	len_key = get_len_key_var(content);
	(*node)->key = ft_substr(content, 0, len_key);
	if (!((*node)->key))
		return (ERROR);
	len_value = ft_strlen(content) - len_key - 1;
	(*node)->value = ft_substr(content, len_key + 1, len_value);
	if (!(*node)->value)
		return (ERROR);
	return (SUCCESS);
}
