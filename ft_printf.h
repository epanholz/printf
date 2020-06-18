/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 18:51:19 by epanholz       #+#    #+#                */
/*   Updated: 2020/01/30 17:38:01 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_format
{
	int		flag;
	int		prec;
	int		conv;
	int		width;
	int		p_width;
	int		bytes_printed;
	int		to_upper;
	int		sign;
}				t_format;

typedef enum	e_flags
{
	ZERO = 0,
	MIN = 1,
	NONE = -1
}				t_flags;

int				ft_printf(const char *format, ...);
int				atoi(const char *str);
unsigned long	count_u(unsigned long n);
long long		count(long long n);
void			print_char(va_list args, t_format **format);
void			print_string(va_list args, t_format **format);
void			print_int(va_list args, t_format **format);
void			print_u_int(va_list args, t_format **format);
void			print_hex(va_list args, t_format **format);
void			print_pointer_address(va_list args, t_format **format);
void			print_width(int flag, t_format **format, int len);
void			print_precision(t_format **format, int len);
void			buf_handler(char const *txt, size_t len, t_format **format);
int				get_width
					(const char *str, int i, t_format **format, va_list args);
int				get_precision
					(const char *str, int i, t_format **format, va_list args);
int				get_flags(const char *str, int i, t_format **format);
void			get_arg_type(char c, t_format **format);
void			print_argument(va_list args, t_format **format);
void			check_format_string
					(const char *format_str, t_format **format, va_list args);
void			itoa(unsigned long value, int base, t_format **format);
int				itoa_hex(unsigned long value);
long long		itoa_check(long long value, t_format **format, int base);
void			padding_zero_none
					(unsigned long value, t_format **format, int base, int len);
void			padding_min
					(unsigned long value, t_format **format, int base, int len);
int				make_format(t_format **format,
					const char *format_str, int index, va_list args);

#endif
