/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:40:05 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/16 11:40:07 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			nbr[12];
	int				len;
	unsigned int	value;

	len = 11;
	nbr[len--] = '\0';
	value = n;
	if (n < 0)
		value = -n;
	while (value >= 10)
	{
		nbr[len--] = (value % 10) + '0';
		value = value / 10;
	}
	nbr[len--] = (value % 10) + '0';
	if (n < 0)
		nbr[len--] = '-';
	ft_putstr_fd(nbr + len + 1, fd);
}
