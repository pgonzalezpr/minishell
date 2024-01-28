/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:12:35 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 12:12:37 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	sanitize_conv_base(t_conversion *conv, unsigned long nbr)
{
	if ((conv->specifier == 'u' || nbr == 0) && conv->specifier != 'p')
		conv->alt_form = 0;
	if (conv->specifier == 'x' || conv->specifier == 'X')
	{
		conv->sign = 0;
		conv->space = 0;
		conv->hex_sep = conv->specifier;
	}
	if (conv->prec != -1)
		conv->zero_padding = 0;
}

char	*build_nbr_base(t_conversion *conv, unsigned long nbr, char *base)
{
	char	*nbr_str;
	char	*buff;

	nbr_str = ft_itoa_base(nbr, base);
	if (!nbr_str)
		return (NULL);
	sanitize_conv_base(conv, nbr);
	conv->buff_width = conv->min_width;
	if (!(conv->prec == 0 && nbr == 0))
		conv->buff_width = get_buff_width(conv, nbr_str);
	buff = malloc((conv->buff_width) * sizeof(char));
	if (!buff)
	{
		free(nbr_str);
		return (NULL);
	}
	fill_blanks(buff, conv->buff_width);
	fill_buff(nbr_str, buff, conv);
	free(nbr_str);
	return (buff);
}

void	sanitize_conv_int(t_conversion *conv, int nbr)
{
	conv->alt_form = 0;
	if (nbr < 0)
	{
		conv->sign = 0;
		conv->space = 0;
	}
	if (conv->prec != -1)
		conv->zero_padding = 0;
}

char	*build_int(t_conversion *conv, int nbr)
{
	char	*nbr_str;
	char	*buff;

	nbr_str = ft_itoa(nbr);
	if (!nbr_str)
		return (NULL);
	sanitize_conv_int(conv, nbr);
	conv->buff_width = get_buff_width(conv, nbr_str);
	buff = malloc((conv->buff_width) * sizeof(char));
	if (!buff)
	{
		free(nbr_str);
		return (NULL);
	}
	fill_blanks(buff, conv->buff_width);
	fill_buff(nbr_str, buff, conv);
	free(nbr_str);
	return (buff);
}

char	*build_ptr(t_conversion *conv, void *ptr)
{
	unsigned long	ptr_nbr;

	conv->alt_form = 1;
	conv->zero_padding = 0;
	conv->sign = 0;
	conv->space = 0;
	conv->prec = -1;
	ptr_nbr = (unsigned long)ptr;
	return (build_nbr_base(conv, ptr_nbr, HEX_LOW_BASE));
}
