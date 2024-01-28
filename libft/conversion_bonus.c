/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:21:59 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 16:22:04 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

t_conversion	*init_conv(void)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (!conv)
		return (NULL);
	conv->alt_form = 0;
	conv->zero_padding = 0;
	conv->left_adjustment = 0;
	conv->sign = 0;
	conv->space = 0;
	conv->min_width = 0;
	conv->prec = -1;
	conv->conv_len = 0;
	conv->specifier = 0;
	conv->buff = NULL;
	conv->buff_width = 0;
	conv->hex_sep = 'x';
	return (conv);
}

void	free_conv(t_conversion *conv)
{
	if (!conv)
		return ;
	if (conv->buff)
		free(conv->buff);
	free(conv);
}

int	parse_conv(const char *format, t_conversion *conv, va_list args)
{
	format += parse_flags(format, conv);
	format += parse_width(format, conv, args);
	format += parse_precision(format, conv, args);
	conv->specifier = *format;
	conv->conv_len++;
	conv->buff = build_buff(conv, args);
	if (!conv->buff)
		return (0);
	return (1);
}

char	*join_buffer(char *first, int first_size, char *second, int second_size)
{
	char	*new;

	new = malloc((first_size + second_size) * sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, first, first_size);
	ft_memcpy(new + first_size, second, second_size);
	return (new);
}

int	handle_conversion(const char *format, char **buffer, int *size,
		va_list args)
{
	t_conversion	*conv;
	char			*tmp;
	int				conv_len;

	conv = init_conv();
	if (!conv)
		return (-1);
	if (!parse_conv(format, conv, args))
	{
		free_conv(conv);
		return (-1);
	}
	tmp = join_buffer(*buffer, *size, conv->buff, conv->buff_width);
	if (!tmp)
	{
		free_conv(conv);
		return (-1);
	}
	free(*buffer);
	*buffer = tmp;
	*size = *size + conv->buff_width;
	conv_len = conv->conv_len;
	free_conv(conv);
	return (conv_len);
}
