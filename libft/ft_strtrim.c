/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:19 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:19 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains(char const *set, char c)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*s1_cpy;
	char	*ptr;

	len = ft_strlen(s1);
	s1_cpy = (char *)s1 + len - 1;
	while (*s1 && ft_contains(set, *s1))
	{
		len--;
		s1++;
	}
	while (len > 0 && ft_contains(set, *s1_cpy))
	{
		len--;
		s1_cpy--;
	}
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}
