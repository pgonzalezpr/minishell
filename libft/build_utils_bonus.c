/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils_bonus.c                                  :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:12:35 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 12:12:37 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	fill_blanks(char *buff, int size)
{
	while (size > 0)
	{
		*buff = ' ';
		buff++;
		size--;
	}
}

char	*ft_itoa_base(unsigned long nbr, char *base)
{
	char			*nbr_str;
	int				offset;
	unsigned int	base_len;
	char			*dup;

	nbr_str = (char *)malloc(65 * sizeof(char));
	if (!nbr_str)
		return (NULL);
	base_len = ft_strlen(base);
	offset = 64;
	nbr_str[offset--] = '\0';
	while (nbr >= base_len)
	{
		nbr_str[offset--] = base[nbr % base_len];
		nbr = nbr / base_len;
	}
	if (nbr == 0)
		nbr_str[offset] = base[0];
	else
		nbr_str[offset] = base[nbr % base_len];
	dup = ft_strdup(nbr_str + offset);
	free(nbr_str);
	return (dup);
}

int	get_buff_width(t_conversion *conv, char *nbr_str)
{
	int	width;
	int	is_negative;

	is_negative = 0;
	if (nbr_str[0] == '-')
	{
		is_negative = 1;
		nbr_str++;
	}
	width = ft_strlen(nbr_str);
	if (conv->prec == 0 && ft_strncmp(nbr_str, "0", ft_strlen(nbr_str)) == 0
		&& conv->specifier != 'p')
		width = 0;
	if (conv->prec > width)
		width = conv->prec;
	if (is_negative)
		width++;
	if (conv->sign || conv->space)
		width++;
	if (conv->alt_form)
		width += 2;
	if (width < conv->min_width)
		width = conv->min_width;
	return (width);
}

void	fill_buff_left(char *nbr_str, char *buff, t_conversion *conv)
{
	int	offset;
	int	copied;

	offset = 0;
	if (conv->sign)
		buff[offset++] = '+';
	else if (conv->space)
		buff[offset++] = ' ';
	if (nbr_str[0] == '-')
	{
		buff[offset++] = '-';
		nbr_str++;
	}
	if (conv->alt_form)
	{
		buff[offset++] = '0';
		buff[offset++] = conv->hex_sep;
	}
	copied = 0;
	while (conv->prec != -1 && copied < conv->prec - (int)ft_strlen(nbr_str))
	{
		buff[offset++] = '0';
		copied++;
	}
	copy_nbr_buff_left(buff, offset, nbr_str, conv);
}

void	fill_buff(char *nbr_str, char *buff, t_conversion *conv)
{
	int	is_negative;
	int	offset;

	is_negative = 0;
	if (conv->left_adjustment)
	{
		conv->zero_padding = 0;
		fill_buff_left(nbr_str, buff, conv);
		return ;
	}
	if (nbr_str[0] == '-')
	{
		is_negative = 1;
		nbr_str++;
	}
	offset = conv->buff_width - 1;
	if (!(conv->prec == 0 && ft_strncmp(nbr_str, "0", ft_strlen(nbr_str)) == 0
			&& conv->specifier != 'p'))
		offset -= copy_nbr_buff(nbr_str, buff, conv);
	if (conv->zero_padding)
		offset -= zero_pad_buff(buff, conv, offset, is_negative);
	offset -= prepend_buff(buff, conv, offset, is_negative);
}
