/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:12:10 by pedro-go          #+#    #+#             */
/*   Updated: 2023/11/12 16:12:11 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FLAGS "-0#+ "
# define BASE_DEC "0123456789"
# define HEX_LOW_BASE "0123456789abcdef"
# define HEX_UP_BASE "0123456789ABCDEF"

typedef struct s_conversion
{
	int		alt_form;
	int		zero_padding;
	int		left_adjustment;
	int		sign;
	int		space;
	int		min_width;
	int		prec;
	int		conv_len;
	char	specifier;
	char	*buff;
	int		buff_width;
	char	hex_sep;
}			t_conversion;

int			handle_conversion(const char *format, char **buffer, int *size,
				va_list args);
int			parse_flags(const char *format, t_conversion *conv);
int			parse_width(const char *format, t_conversion *conv, va_list args);
int			parse_precision(const char *format, t_conversion *conv,
				va_list args);
char		*build_buff(t_conversion *conv, va_list args);
char		*build_char(t_conversion *conv, char c);
char		*build_str(t_conversion *conv, char *str);
char		*build_ptr(t_conversion *conv, void *ptr);
char		*build_int(t_conversion *conv, int nbr);
char		*build_nbr_base(t_conversion *conv, unsigned long nbr, char *base);
void		fill_blanks(char *str, int size);
char		*ft_itoa_base(unsigned long nbr, char *base);
int			get_buff_width(t_conversion *conv, char *nbr_str);
void		fill_buff(char *nbr_str, char *buff, t_conversion *conv);
int			zero_pad_buff(char *buff, t_conversion *conv, int offset,
				int is_negative);
int			copy_nbr_buff(char *nbr_str, char *buff, t_conversion *conv);
int			prepend_buff(char *buff, t_conversion *conv, int offset,
				int is_negative);
char		*join_buffer(char *first, int first_size, char *second,
				int second_size);
void		copy_nbr_buff_left(char *buff, int offset, char *nbr_str,
				t_conversion *conv);

#endif