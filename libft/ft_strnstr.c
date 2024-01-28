/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:17 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:18 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_string(const char *big, const char *little, size_t len)
{
	while (*little && *big == *little && len > 0)
	{
		big++;
		little++;
		len--;
	}
	return (!*little);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		if (*big == *little && compare_string(big, little, len))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
