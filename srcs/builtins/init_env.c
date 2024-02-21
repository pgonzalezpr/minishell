/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:42:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/21 15:35:36 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Devuelve la longitud de la clave del env.
*/
static int	get_len_key_var(char *key)
{
	int	len;

	len = 0;
	while (key && *key != EQUAL)
	{
		len++;
		key++;
	}
	return (len);
}

/*
* PRE: -
* POST: Devuelve un nodo nuevo del env.
*/
static t_env	*get_new_node_env(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

/*
* PRE: -
* POST: inicializa el env.
*/
int	init_env(t_minishell *minishell, char **env)
{
	t_env	*tmp;
	int		i;
	int		len_key;
	int		len_value;

	i = -1;
	while (env[++i])
	{
		tmp = get_new_node_env(NULL, NULL);
		minishell->env = tmp;
		if (!tmp)
			return (ERROR);
		len_key = get_len_key_var(env[i]);
		len_value = ft_strlen(env[i]) - len_key;
		tmp->key = (char *)malloc(len_key + 1);
		if (!tmp->key)
			return (ERROR);
		tmp->value = (char *)malloc(len_value + 1);
		if (!tmp->value)
			return (ERROR);
		tmp->key = ft_strdup("KEY");
		tmp->value = ft_strdup("VALUE");
		printf("KEY: %s | VALUE:%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
		minishell->env = tmp;
	}
	return (SUCCESS);
}
