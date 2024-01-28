/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:08 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:09 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_split_len(char const *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static int	count_words(char const *str, char c)
{
	int	count;
	int	searching;

	count = 0;
	searching = 1;
	while (*str)
	{
		if (searching && *str != c)
		{
			count++;
			searching = 0;
		}
		if (*str == c)
			searching = 1;
		str++;
	}
	return (count);
}

static char	**fill_word_arr(char const *s, char **word_arr, char c)
{
	int		offset;
	int		searching;
	char	*word;

	offset = 0;
	searching = 1;
	while (*s)
	{
		if (searching && *s != c)
		{
			word = malloc((word_split_len(s, c) + 1) * sizeof(char));
			if (!word)
				return (NULL);
			ft_strlcpy(word, s, word_split_len(s, c) + 1);
			word_arr[offset++] = word;
			searching = 0;
		}
		if (*s == c)
			searching = 1;
		s++;
	}
	word_arr[offset] = NULL;
	return (word_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**word_arr;

	word_arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!word_arr)
		return (NULL);
	return (fill_word_arr(s, word_arr, c));
}
