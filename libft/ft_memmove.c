/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:02 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:03 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	len;

	if (!src && !dest)
		return (dest);
	len = 0;
	if (src < dest)
	{
		len = n;
		while (len > 0)
		{
			len--;
			((char *)dest)[len] = ((char *)src)[len];
		}
	}
	else
	{
		len = 0;
		while (len < n)
		{
			((char *)dest)[len] = ((char *)src)[len];
			len++;
		}
	}
	return (dest);
}
