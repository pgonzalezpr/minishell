/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:40:46 by pedro-go          #+#    #+#             */
/*   Updated: 2023/09/17 13:42:05 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>

int	ft_printf_int(int nbr);
int	ft_putnbr_base(unsigned long nbr, char *base);
int	ft_printf_string(char *s);
int	ft_printf_pointer(void *ptr);
int	convert(const char conv, va_list args);

#endif // PRINTF_UTILS_H
