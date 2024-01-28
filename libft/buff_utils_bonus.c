/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_utils_bonus.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:12:35 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 12:12:37 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	copy_nbr_buff_left(char *buff, int offset, char *nbr_str,
		t_conversion *conv)
{
	if (!(conv->prec == 0 && ft_strncmp(nbr_str, "0", ft_strlen(nbr_str)) == 0
			&& conv->specifier != 'p'))
		ft_memcpy(buff + offset, nbr_str, ft_strlen(nbr_str));
}

int	copy_nbr_buff(char *nbr_str, char *buff, t_conversion *conv)
{
	int	len;
	int	copied;
	int	offset;

	len = ft_strlen(nbr_str);
	copied = 0;
	ft_memcpy(buff + (conv->buff_width - len), nbr_str, len);
	copied += len;
	offset = conv->buff_width - len - 1;
	if (conv->prec == -1)
		return (copied);
	while (copied < conv->prec)
	{
		buff[offset--] = '0';
		copied++;
	}
	return (copied);
}

int	zero_pad_buff(char *buff, t_conversion *conv, int offset, int is_negative)
{
	int	space_requirement;
	int	copied;

	space_requirement = 0;
	copied = 0;
	if (conv->sign || conv->space || is_negative)
		space_requirement++;
	if (conv->alt_form)
		space_requirement += 2;
	while (offset >= space_requirement)
	{
		buff[offset--] = '0';
		copied++;
	}
	return (copied);
}

int	prepend_buff(char *buff, t_conversion *conv, int offset, int is_negative)
{
	int	copied;

	copied = 0;
	if (conv->sign)
	{
		buff[offset--] = '+';
		copied++;
	}
	else if (conv->space)
	{
		buff[offset--] = ' ';
		copied++;
	}
	if (is_negative)
	{
		buff[offset--] = '-';
		copied++;
	}
	if (conv->alt_form)
	{
		buff[offset--] = conv->hex_sep;
		buff[offset--] = '0';
		copied += 2;
	}
	return (copied);
}
