/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:42 by brayan            #+#    #+#             */
/*   Updated: 2024/02/22 17:59:11 by brayan           ###   ########.fr       */
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
* POST: Agrega el new_content al node, cambiando su valor
*		y clave por dicho contenido.
*/
int	set_node_content(char *content, t_env **node)
{
	int		i;
	int		len_key;
	int		len_value;	

	i = 0;
	len_key = get_len_key_var(content);
	(*node)->key = (char *)malloc(len_key);
	if (!((*node)->key))
		return (ERROR);
	len_value = ft_strlen(content) - len_key;
	(*node)->value = (char *)malloc(len_value);
	if (!((*node)->value))
		return (ERROR);
	while (content[i] && content[i] != EQUAL)
	{
		(*node)->key[i] = content[i];
		i++;
	}
	(*node)->key[i] = NULL_STR;
	(*node)->value = ft_strdup(&content[len_key]);
	if (!(*node)->value)
		return (ERROR);
	(*node)->value++;
	return (SUCCESS);
}
