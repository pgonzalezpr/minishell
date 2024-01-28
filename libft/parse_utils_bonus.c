/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:56:59 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 17:57:01 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	parse_flags(const char *format, t_conversion *conv)
{
	int	count;

	count = 0;
	while (ft_strchr(FLAGS, *format) != 0)
	{
		if (*format == '-')
			conv->left_adjustment = 1;
		if (*format == '0')
			conv->zero_padding = 1;
		if (*format == '#')
			conv->alt_form = 1;
		if (*format == '+')
			conv->sign = 1;
		if (*format == ' ')
			conv->space = 1;
		count++;
		format++;
	}
	conv->conv_len += count;
	return (count);
}

int	parse_width(const char *format, t_conversion *conv, va_list args)
{
	int	count;
	int	width;

	if (*format == '*')
	{
		conv->min_width = va_arg(args, int);
		conv->conv_len += 1;
		return (1);
	}
	count = 0;
	width = 0;
	while (ft_isdigit(*format))
	{
		width = width * 10 + (*format - '0');
		count++;
		format++;
	}
	conv->min_width = width;
	conv->conv_len += count;
	return (count);
}

int	parse_precision(const char *format, t_conversion *conv, va_list args)
{
	int	count;
	int	precision;

	if (*format != '.')
		return (0);
	format++;
	if (*format == '*')
	{
		conv->prec = va_arg(args, int);
		conv->conv_len += 2;
		return (2);
	}
	count = 1;
	precision = 0;
	while (ft_isdigit(*format))
	{
		precision = precision * 10 + (*format - '0');
		count++;
		format++;
	}
	conv->prec = precision;
	conv->conv_len += count;
	return (count);
}

char	*build_buff(t_conversion *conv, va_list args)
{
	char	sp;

	sp = conv->specifier;
	if (sp == 'c')
		return (build_char(conv, (char)va_arg(args, int)));
	if (sp == 's')
		return (build_str(conv, va_arg(args, char *)));
	if (sp == 'p')
		return (build_ptr(conv, va_arg(args, void *)));
	if (sp == 'd' || sp == 'i')
		return (build_int(conv, va_arg(args, int)));
	if (sp == 'u')
		return (build_nbr_base(conv, va_arg(args, unsigned int), BASE_DEC));
	if (sp == 'x')
		return (build_nbr_base(conv, va_arg(args, unsigned int), HEX_LOW_BASE));
	if (sp == 'X')
		return (build_nbr_base(conv, va_arg(args, unsigned int), HEX_UP_BASE));
	if (sp == '%')
		return (build_char(conv, '%'));
	return (NULL);
}
