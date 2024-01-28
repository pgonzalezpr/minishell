/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:01 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:02 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*dest_copy;

	if (!src && !dest)
		return (dest);
	dest_copy = dest;
	while (n > 0)
	{
		*((char *)dest++) = *((char *)src++);
		n--;
	}
	return (dest_copy);
}
