/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:13 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:14 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	offset;

	offset = 0;
	if (size > 0)
	{
		offset = 0;
		while (src[offset] && size > 1)
		{
			dst[offset] = src[offset];
			offset++;
			size--;
		}
		dst[offset] = '\0';
	}
	while (src[offset])
		offset++;
	return (offset);
}
