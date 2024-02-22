/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:44:13 by pedro-go          #+#    #+#             */
/*   Updated: 2024/02/22 14:34:47 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	current = *lst;
	if (!current)
		ft_lstadd_front(lst, new);
	else
	{
		current = ft_lstlast(current);
		current->next = new;
	}
}
