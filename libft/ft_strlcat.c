/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:12 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:13 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	total_len = dst_len + src_len;
	if (size > dst_len)
	{
		dst += dst_len;
		size -= dst_len;
		if (src_len >= size)
			src_len = size - 1;
		ft_memcpy(dst, src, src_len);
		dst[src_len] = '\0';
		return (total_len);
	}
	else
		dst_len = size;
	return (dst_len + src_len);
}
