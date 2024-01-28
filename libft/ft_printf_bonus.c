/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:12:35 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 12:12:37 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

char	*build_char(t_conversion *conv, char c)
{
	char	*buff;
	int		offset;

	conv->buff_width = 1;
	if (conv->min_width > conv->buff_width)
		conv->buff_width = conv->min_width;
	buff = malloc((conv->buff_width) * sizeof(char));
	if (!buff)
		return (NULL);
	fill_blanks(buff, conv->buff_width);
	if (conv->left_adjustment)
		buff[0] = c;
	else
	{
		offset = conv->buff_width - 1;
		buff[offset--] = c;
		if (conv->zero_padding)
		{
			while (offset >= 0)
				buff[offset--] = '0';
		}
	}
	return (buff);
}

char	*build_str(t_conversion *conv, char *str)
{
	int		len;
	char	*buff;
	int		start;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (conv->prec != -1 && conv->prec < len)
		len = conv->prec;
	conv->buff_width = len;
	if (conv->buff_width < conv->min_width)
		conv->buff_width = conv->min_width;
	buff = malloc((conv->buff_width) * sizeof(char));
	if (!buff)
		return (NULL);
	fill_blanks(buff, conv->buff_width);
	start = conv->buff_width - len;
	if (conv->left_adjustment)
		start = 0;
	ft_memcpy(buff + start, str, len);
	return (buff);
}

int	handle_non_conversion(const char *format, char **buffer, int *size)
{
	int		count;
	char	*start;
	char	*arr;
	char	*join;

	count = 0;
	start = (char *)format;
	while (*format && *format != '%')
	{
		format++;
		count++;
	}
	arr = malloc(count * sizeof(char));
	if (!arr)
		return (-1);
	ft_memcpy(arr, start, count);
	join = join_buffer(*buffer, *size, arr, count);
	free(arr);
	free(*buffer);
	*buffer = join;
	*size = *size + count;
	return (count);
}

int	process_format(const char *format, va_list args, char **buffer, int *size)
{
	int	conv_len;
	int	non_conv_len;

	while (*format)
	{
		if (*format != '%')
		{
			non_conv_len = handle_non_conversion(format, buffer, size);
			if (non_conv_len == -1)
				return (0);
			format += non_conv_len;
		}
		if (*format == '%')
		{
			conv_len = handle_conversion(++format, buffer, size, args);
			if (conv_len == -1)
				return (0);
			format += conv_len;
		}
	}
	return (1);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		size;
	char	*buffer;

	va_start(args, format);
	buffer = NULL;
	size = 0;
	if (!process_format(format, args, &buffer, &size))
	{
		free(buffer);
		return (-1);
	}
	va_end(args);
	if (write(fd, buffer, size) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (size);
}
