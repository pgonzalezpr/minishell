/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:18 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:19 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_last;

	s_last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			s_last = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (s_last);
}
